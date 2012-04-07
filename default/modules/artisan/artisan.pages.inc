<?php

define('MAX_TITLE_LENGTH_ARTISAN_ITEMS',45);

/**
 * Present an artisan submission form.
 */
function artisan_add() {
  global $user;
  
  $artisan = entity_get_controller('artisan')->create();

  drupal_set_title(t('Create Artisan Profile'), PASS_THROUGH);
  return drupal_get_form('artisan_form', $artisan);
}

/**
 * Menu callback; presents the artisan editing form, or redirects to delete confirmation.
 *
 * @param $artisan
 *   The artisan object to edit.
 */
function artisan_page_edit($artisan) {
  drupal_set_title(t('<em>Edit @title', array('@title' => $artisan->name)), PASS_THROUGH);

  return drupal_get_form('artisan_form', $artisan);
}

/**
 * Form builder; Displays the artisan add/edit form.
 *
 * @param $form
 * @param $form_state
 * @param $artisan
 *   The artisan object to edit, which may be brand new.
 */
function artisan_form($form, &$form_state, $artisan) {

  // Set the id and identify this as an artisan edit form.
  $form['#id'] = 'artisan-form';

  // Save the artisan for later, in case we need it.
  $form['#artisan'] = $artisan;
  $form_state['artisan'] = $artisan;
  
  // Common fields. We don't have many.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#weight' => -12,
    '#required' => TRUE,
    '#default_value' => $artisan->name,
  );
  
  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#weight' => -11,
    '#required' => TRUE,
    '#default_value' => $artisan->city,
  );
  
  $form['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#weight' => -10,
    '#required' => TRUE,
	'#options' => array('MX' => 'Mexico', 'UZ' => 'Uzbekistan'),
    '#default_value' => $artisan->country,
  );
  
  $form['local_location'] = array(
    '#type' => 'textfield',
    '#title' => t('Where to find (Address, Beach, other Description)'),
    '#weight' => -9,
    '#required' => False,
    '#default_value' => $artisan->local_location,
  );
  
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#cols' => 60,
    '#rows' => 5,
    '#weight' => -7,
    '#resizable' => FALSE,
    '#required' => TRUE,
    '#default_value' => $artisan->description,
  );
  
  $form['video_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Video Link (YouTube)'),
    '#weight' => -5,
    '#required' => FALSE,
    '#default_value' => $artisan->video_link,
  );
  
  // Add the buttons.
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('artisan_form_submit'),
  );
  if (!empty($artisan->artisan_id)) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete artisans'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('artisan_form_delete_submit'),
    );
  }

  $form['#validate'][] = 'artisan_form_validate';

  field_attach_form('artisan', $artisan, $form, $form_state);

  return $form;
}

function artisan_form_validate($form, &$form_state) {
  $artisan = $form_state['artisan'];

  // Field validation.
  field_attach_form_validate('artisan', $artisan, $form, $form_state);
}


function artisan_form_submit($form, &$form_state) {
  global $user;

  $artisan = &$form_state['artisan'];
  
  // Save the uploaded file from temp to permanent storage.
  $file_info = file_load($form_state['field']['field_profile_picture']['und']['items'][0]['fid']);
  file_move($file_info,'public://',FILE_EXISTS_RENAME);

  $artisan->description = $form_state['values']['description'];
  $artisan->name = $form_state['values']['name'];
  $artisan->city = $form_state['values']['city'];
  $artisan->country = $form_state['values']['country'];
  $artisan->local_location = $form_state['values']['local_location'];
  $artisan->album_id = $file_info->fid;//$form_state['values']['album_id'];
  $artisan->video_link = $form_state['values']['video_link'];
  
  if(empty($artisan->listing_date)) {
    $artisan->listing_date = REQUEST_TIME;
  }
  
  $artisan->last_updated = REQUST_TIME;
  
  // Notify field widgets.
  field_attach_submit('artisan', $artisan, $form, $form_state);

  // Save the artisan.
  artisan_save($artisan);
 
  // Notify the user.
  drupal_set_message(t('artisan saved.'));

  $form_state['redirect'] = 'artisan/' . $artisan->artisan_id;
}


function artisan_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $artisan = $form['#artisan'];
  $form_state['redirect'] = array('artisan/' . $artisan->artisan_id . '/delete', array('query' => $destination));
}

function artisan_extract_profile_info($elements) {
  $artisan = $elements['#artisan'];
  

  return $elements;
}

function template_preprocess_artisan_items_area(&$variables) {
  $artisan = $variables['artisan'];
  
  $artisan_items = artworks_get_artisan_artworks($artisan->artisan_id);
  
  $items_to_display = array();
  
  foreach($artisan_items as $item) {
    for($i = 0; $i < 10; $i++) {
    $title = $item->title;
    if(strlen($title) > MAX_TITLE_LENGTH_ARTISAN_ITEMS) {
      $title = substr($title,0,MAX_TITLE_LENGTH_ARTISAN_ITEMS) . '...';
    }
	
    $file_info = file_load($item->album_id);
    $image_url = $file_info->uri;
    $items_to_display[] = array(
	  'title' => $title,
	  'image_url' => $image_url,
	  'price' => $item->max_price,
	);
	}
  }
  
  $variables['items'] = $items_to_display;  
}

function template_preprocess_profile_similar_artisans(&$variables) {
  $artisan = $variables['artisan'];
  
  $similar_artisans = artisan_get_similar_artisans($artisan->artisan_id,5);
  
  $artisans_to_display = array();
  
  foreach($similar_artisans as $item) {
    $name = check_plain($item->name);
	if(strlen($name) > MAX_ARTISAN_NAME_LENGTH) {
  	  $name = substr($name,0,MAX_ARTISAN_NAME_LENGTH) . '...';
	}
	
    $file_info = file_load($item->album_id);
    $image_url = $file_info->uri;
    $artisans_to_display[] = array(
	  'name' => $name,
	  'artisan_id' => $item->artisan_id,
	  'image_url' => $image_url,
	);
  }
  
  $variables['similar_artisans'] = $artisans_to_display;
}

function template_preprocess_profile_image_area(&$variables) {
  $artisan = $variables['artisan'];
  
  $variables['images'] = null;
  
  if(isset($artisan->album_id)){
	  // Find the image URI.
	  $image_file = file_load($artisan->album_id);
	  
	  if(isset($image_file->uri)){
		$variables['images'] = array($image_file->uri,$image_file->uri,$image_file->uri,$image_file->uri,$image_file->uri,$image_file->uri,$image_file->uri,$image_file->uri);
	  }
  }
}

function template_preprocess_profile_video_area(&$variables) {
  $artisan = $variables['artisan'];
  
  $variables['youtube_id'] = null;
  
  // Find the image URI.
  if(isset($artisan->video_link)){
    $video_link = $artisan->video_link;
    
    // Parse video URL to extract YouTube video code.
    if($res = preg_match('/http:\/\/www.youtube.com\/watch\?v=(\w*)/i',  $video_link, $matches) == 1) {
	  $youtube_id = $matches[1];
      $variables['youtube_id'] = $youtube_id;
    }
  }
}



function template_preprocess_profile_info_area(&$variables) {
  $artisan = $variables['artisan'];
  
  // Find the image URI.
  $image_file = file_load($artisan->album_id);
	
  $name = check_plain($artisan->name);
	
  $variables['name'] = $name;
  $variables['video_link'] = $artisan->video_link;
  $variables['artisan_id'] = check_plain($artisan->artisan_id);
  $variables['description'] = check_plain($artisan->description);
  $variables['created'] = $artisan->created;
  $variables['date'] = format_date($artisan->created,'custom','F d, Y');
}

/**
 * Displays an artisan.
 *
 * @param $artisan
 *   The artisan object to display.
 * @param $view_mode
 *   The view mode we want to display.
 */
function artisan_page_view($artisan, $view_mode = 'full') {
  // Remove previously built content, if exists.
  $artisan->content = array();
  
  if ($view_mode == 'teaser') {
    $artisan->content['title'] = array(
      '#markup' => filter_xss($artisan->name),
      '#weight' => -5,
    );
	field_attach_prepare_view('artisan', array($artisan->artisan_id => $artisan), $view_mode);
    entity_prepare_view('artisan', array($artisan->artisan_id => $artisan));
    $artisan->content += field_attach_view('artisan', $artisan, $view_mode);  
  }else if($view_mode == 'full') {
    //$content = $artisan->buildContent($artisan,$view_mode);
	$content = array( //parent::buildContent($artisan, $view_mode, $langcode, $content);
	  '#entity_type' => 'artisan',
      '#bundle' => 'artisan',
    );
	
	$content['artisan_profile_page'] = array(
	  '#prefix' => '<div class="artisan_profile_page clearfix">',
	  'profile_left_column' => array(
	    '#prefix' => '<div class="profile_left_column clearfix">',
		'profile_image_area' => array(
	      '#prefix' => '<div class="profile_image_area clearfix">',
		  '#markup' => theme('profile_image_area',array('artisan' => $artisan)),
		  '#suffix' => '</div>',
	    ),
		'profile_video_area' => array(
	      '#prefix' => '<div class="profile_video_area clearfix">',
		  '#markup' => theme('profile_video_area',array('artisan' => $artisan)),
		  '#suffix' => '</div>',
	    ),
		'profile_become_artisan_helper' => array(
	      '#prefix' => '<div class="profile_become_artisan_helper clearfix">',
		  '#suffix' => '</div>',
	    ),
		'#suffix' => '</div>',
	  ),
	  'profile_right_column' => array(
	    '#prefix' => '<div class="profile_right_column clearfix">',
	    'personal_info_area' => array(
		  //'#theme' => 'profile_info_area',
		  //'#artisan' => $artisan,
		  '#markup' => theme('profile_info_area',array('artisan' => $artisan)),
		  '#prefix' => '<div class="personal_info_area clearfix">',
		  '#suffix' => '</div>',
		  '#attached' => array(
		    'library' => array(array('artisan','profile_pickachoose_gallery')),
			'js' => array( drupal_get_path('module','artisan') . '/profile_gallery.js'),
		  ),
			
		),
		'artisan_items_area' => array(
	      '#prefix' => '<div class="artisan_items_area clearfix">',
		  '#markup' => theme('artisan_items_area',array('artisan' => $artisan)),
		  '#suffix' => '</div>',
		),
		'#suffix' => '</div>',
	  ),
	  'profile_footer_area' => array(
	    '#prefix' => '<div class="profile_footer_area clearfix">',
	    'profile_similar_artisans' => array(
	      '#prefix' => '<div class="profile_similar_artisans clearfix">',
		  '#markup' => theme('profile_similar_artisans',array('artisan' => $artisan)),
		  '#suffix' => '</div>',
		),
		'#suffix' => '</div>',
	  ),
	  '#suffix' => '</div>',
	  '#attached' => array(
	     'css' => array( drupal_get_path('module','artisan') . '/artisan_page.css' ),
	  ),
	);
	/*
	
	$content['artisan_teaser'] =  array(
      '#markup' => theme(
	    'artisan_profile_page', array(
  	      'name' => $name,
	      'image_uri' => $image_file->uri,
	      'video_link' => $artisan->video_link,
	      'artisan_id' => check_plain($artisan->artisan_id),
		  'description' => check_plain($artisan->description),
	    )
	  )
	);
	*/  
	$artisan->content = drupal_render($content);
  }	
  
  return $artisan->content;
}

/**
 * Form bulder; Asks for confirmation of artisan deletion.
 */
function artisan_delete_confirm($form, &$form_state, $artisan) {
  $form['#artisan'] = $artisan;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['artisan_id'] = array('#type' => 'value', '#value' => $artisan->artisan_id);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $artisan->name)),
    'artisan/' . $artisan->artisan_id,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Executes artisan deletion.
 */
function artisan_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $artisan = artisan_load($form_state['values']['artisan_id']);
    artisan_delete($form_state['values']['artisan_id']);
    watchdog('artisan', 'Deleted %title.', array('%title' => $artisan->name));

    drupal_set_message(t('%title has been deleted.', array('%title' => $artisan->name)));
  }

  $form_state['redirect'] = '<front>';
}
