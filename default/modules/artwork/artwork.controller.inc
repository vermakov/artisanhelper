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
											'artisan_name' => check_plain($artisan->name),
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
	  'ebay_id' => '',
	  'tags' => '',
	  'short_description' => '',
	  'currency' => 'USD'
	);

    $model = parent::create($values);
    return $model;
  }
}
