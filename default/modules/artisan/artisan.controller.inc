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
	
	  $name = check_plain($entity->name);
	  if(strlen($name) > MAX_ARTISAN_NAME_LENGTH) {
  	    $name = substr($name,0,MAX_ARTISAN_NAME_LENGTH) . '...';
	  }
      $short_description = $entity->description;
      if(strlen($short_description) > 1000 ) {
        $short_description = substr($short_description,0,1000) . '...';
      }
      $content['artisan_teaser'] =  array(
        '#markup' => theme(
	      'artisan_teaser', array(
  	        'name' => $name,
		    'image_uri' => $image_file->uri,
		    'artisan_id' => check_plain($entity->artisan_id),
		    'short_description' => check_plain($short_description)
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
	
	  $name = check_plain($entity->name);
	  
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
      'name' => '',
	  'city' => '',
	  'country' => 'MX',
	  'local_location' => '',
	  'photo' => '',
	  'video_link' => '',
	  'description' => '',
	);
    $model = parent::create($values);
    return $model;
  }  
}
