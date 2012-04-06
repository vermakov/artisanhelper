<?php

define('MAX_TITLE_LENGTH',45);

/**
 * The class used for artwork entities
 */
class ArtworkClass extends Entity {
  
  public function __construct($values = array()) {
    parent::__construct($values, 'artwork');
  }

  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'artwork/' . $this->item_id);
  }
}

/**
 * Controller for loading, creating, and saving artworks.
 *
 * The default loader, which we extend, handles load() already. We only
 * need to add saving and creating.
 */
class ArtworkEntityController extends EntityAPIController {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }
  
  /**
   * Overriding the buldContent function to add entity specific fields
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    
	$content = parent::buildContent($entity, $view_mode, $langcode, $content);
	
	if($view_mode == 'teaser') {
	  // Find the image URI.
	  $image_file = file_load($entity->album_id);
	  $artisan = artisan_get_by_id($entity->artisan_id);
	
	  $title = $entity->title;
	  if(strlen($title) > MAX_TITLE_LENGTH) {
  	    $title = substr($title,0,MAX_TITLE_LENGTH) . '...';
	  }
	
      $content['artwork_teaser'] =  array(
        '#markup' => theme('artwork_teaser', array(
											'title' => check_plain($title),
											'price' => check_plain($entity->max_price),
											'item_id' => check_plain($entity->item_id),
											'image_uri' => $image_file->uri,
											'artisan_id' => check_plain($entity->artisan_id),
											'artisan_name' => check_plain($artisan->first_name . ' ' . $artisan->last_name),
											)));
	} else if($view_mode == 'full') {
	
	
	}
    return $content;
  }
  
  /**
   * Create a model - we first set up the values that are specific
   * to our model schema but then also go through the EntityAPIController
   * function.
   * 
   * @param $type
   *   The machine-readable type of the model.
   *
   * @return
   *   A model object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Model
	
	$values += array(
	  'item_id' => '',
      'title' => '',
	  'description' => '',
	  'artisan_id' => '',
      'max_price' => '',
      'category' => '',
      'materials' => '',
      'etsy_id' => '',
	  'short_description' => ''
	);

    $model = parent::create($values);
    return $model;
  }
}
 
class ArtworkController extends DrupalDefaultEntityController {

  public function save($artwork) {
    $transaction = db_transaction();

    try {
      global $user;

      // Determine if we will be inserting a new artwork.
      $artwork->is_new = empty($artwork->item_id);

      // Set the timestamp fields.
      if (empty($artwork->created)) {
        $artwork->listing_date = REQUEST_TIME;
      }
      $artwork->last_updated = REQUEST_TIME;

      $update_artwork = TRUE;

      // Give modules the opportunity to prepare field data for saving.
      field_attach_presave('artwork', $artwork);


      // If this is a new artwork...
      if ($artwork->is_new) {
        // Save the new artwork.
        drupal_write_record('item_pages', $artwork);

        $op = 'insert';
      }
      else {
        // Save the updated artwork.
        drupal_write_record('item_pages', $artwork, 'item_id');

        $op = 'update';
      }

      // Save fields.
      $function = 'field_attach_' . $op;
      $function('artwork', $artwork);

      module_invoke_all('entity_' . $op, $artwork, 'artwork');

      // Clear internal properties.
      unset($artwork->is_new);

      // Ignore slave server temporarily to give time for the saved order to be
      // propagated to the slave.
      db_ignore_slave();

      return $artwork;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('artwork', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Deletes multiple artworks by ID.
   *
   * @param $aids
   *   An array of artwork IDs to delete.
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($aids) {
    if (!empty($aids)) {
      $artworks = $this->load($aids, array());

      $transaction = db_transaction();

      try {
        db_delete('item_pages')
          ->condition('item_id', $aids, 'IN')
          ->execute();

        foreach ($artworks as $item_id => $artwork) {
          field_attach_delete('artwork', $artwork);
        }

        // Ignore slave server temporarily to give time for the
        // saved artwork to be propagated to the slave.
        db_ignore_slave();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('artwork', $e, NULL, WATCHDOG_ERROR);
        return FALSE;
      }

      module_invoke_all('entity_delete', $artwork, 'artwork');

      // Clear the page and block and artwork caches.
      cache_clear_all();
      $this->resetCache();
    }

    return TRUE;
  }

  /**
   * Create a default artwork.
   *
   * @param $type
   *   The machine-readable type of the artwork.
   *
   * @return
   *   An artwork object with all default fields initialized.
   */
  public function create() {
    return (object) array(
      'item_id' => '',
      'title' => '',
	  'description' => '',
	  'artisan_id' => '',
      'max_price' => '',
      'category' => '',
      'materials' => '',
      'etsy_id' => '',
	  'short_description' => ''
    );
  }

}
