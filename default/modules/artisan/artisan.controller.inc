<?php

define('MAX_ARTISAN_NAME_LENGTH',30);

/**
 * Controller for loading, creating, and saving artworks.
 *
 * The default loader, which we extend, handles load() already. We only
 * need to add saving and creating.
 */
class ArtisanEntityController extends EntityAPIController {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * Overriding the buldContent function to add entity specific fields
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
  
    if($view_mode == 'teaser') {
      $content = array( //parent::buildContent($entity, $view_mode, $langcode, $content);
	    '#entity_type' => 'artisan',
        '#bundle' => 'artisan',
      );
    
	  // Find the image URI.
	  $image_file = file_load($entity->album_id);
	  $artisan = artisan_get_by_id($entity->artisan_id);
	
	  $name = check_plain($entity->first_name . ' ' . $entity->last_name);
	  if(strlen($name) > MAX_ARTISAN_NAME_LENGTH) {
  	    $name = substr($name,0,MAX_ARTISAN_NAME_LENGTH) . '...';
	  }
	  
      $content['artisan_teaser'] =  array(
        '#markup' => theme(
	      'artisan_teaser', array(
  	        'name' => $name,
		    'image_uri' => $image_file->uri,
		    'artisan_id' => check_plain($entity->artisan_id),
		    'short_description' => check_plain($entity->description),
	      )
	    )
	  );
	}
	else if ($view_mode == 'full') {
	  $content = '';
	/*  $content = array( //parent::buildContent($entity, $view_mode, $langcode, $content);
	    '#entity_type' => 'artisan',
        '#bundle' => 'artisan',
      );

	  // Find the image URI.
	  $image_file = file_load($entity->album_id);
	
	  $name = check_plain($entity->first_name . ' ' . $entity->last_name);
	  
	  $content['artisan_teaser'] =  array(
        '#markup' => theme(
	      'artisan_profile_page', array(
  	        'name' => $name,
		    'image_uri' => $image_file->uri,
			'vieo_link' => $entity->video_link,
		    'artisan_id' => check_plain($entity->artisan_id),
		    'description' => check_plain($entity->description),
	      )
	    )
	  );
	*/  
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
      'artisan_id' => '',
      'first_name' => '',
	  'last_name' => '',
	  'photo' => '',
	  'video_link' => '',
	  'description' => '',
	);
    $model = parent::create($values);
    return $model;
  }  
}

/**
 * Controller for loading, creating, and saving artisans.
 *
 * The default loader, which we extend, handles load() already. We only
 * need to add saving and creating.
 */
class ArtisanController extends DrupalDefaultEntityController {

  public function save($artisan) {
    $transaction = db_transaction();

    try {
      global $user;

      // Determine if we will be inserting a new artisan.
      $artisan->is_new = empty($artisan->artisan_id);

      // Set the timestamp fields.
      if (empty($artisan->created)) {
        $artisan->created = REQUEST_TIME;
      }
      $artisan->changed = REQUEST_TIME;

      $update_artisan = TRUE;

      // Give modules the opportunity to prepare field data for saving.
      field_attach_presave('artisan', $artisan);


      // If this is a new artisan...
      if ($artisan->is_new) {
        // Save the new artisan.
        drupal_write_record('artisan_profiles', $artisan);

        $op = 'insert';
      }
      else {
        // Save the updated artisan.
        drupal_write_record('artisan_profiles', $artisan, 'artisan_id');

        $op = 'update';
      }

      // Save fields.
      $function = 'field_attach_' . $op;
      $function('artisan', $artisan);

      module_invoke_all('entity_' . $op, $artisan, 'artisan');

      // Clear internal properties.
      unset($artisan->is_new);

      // Ignore slave server temporarily to give time for the saved order to be
      // propagated to the slave.
      db_ignore_slave();

      return $artisan;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('artisan', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Deletes multiple artisans by ID.
   *
   * @param $aids
   *   An array of artisan IDs to delete.
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($aids) {
    if (!empty($aids)) {
      $artisans = $this->load($aids, array());

      $transaction = db_transaction();

      try {
        db_delete('artisan_profiles')
          ->condition('artisan_id', $aids, 'IN')
          ->execute();

        foreach ($artisans as $artisan_id => $artisan) {
          field_attach_delete('artisan', $artisan);
        }

        // Ignore slave server temporarily to give time for the
        // saved artisan to be propagated to the slave.
        db_ignore_slave();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('artisan', $e, NULL, WATCHDOG_ERROR);
        return FALSE;
      }

      module_invoke_all('entity_delete', $artisan, 'artisan');

      // Clear the page and block and artisan caches.
      cache_clear_all();
      $this->resetCache();
    }

    return TRUE;
  }

  /**
   * Create a default artisan.
   *
   * @param $type
   *   The machine-readable type of the artisan.
   *
   * @return
   *   An artisan object with all default fields initialized.
   */
  public function create() {
    return (object) array(
      'artisan_id' => '',
      'first_name' => '',
	  'last_name' => '',
	  'photo' => '',
	  'video_link' => '',
	  'description' => ''
    );
  }
}
