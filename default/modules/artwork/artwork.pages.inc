<?php

function artwork_add() {
  global $user;
  
  $artwork = entity_get_controller('artwork')->create();

  drupal_set_title(t('Create artwork Profile'), PASS_THROUGH);
  return drupal_get_form('artwork_form', $artwork);
}

/**
 * Menu callback; presents the artwork editing form, or redirects to delete confirmation.
 *
 * @param $artwork
 *   The artwork object to edit.
 */
function artwork_page_edit($artwork) {
  drupal_set_title(t('<em>Edit @title', array('@title' => $artwork->title)), PASS_THROUGH);

  return drupal_get_form('artwork_form', $artwork);
}

/**
 * Form builder; Displays the artwork add/edit form.
 *
 * @param $form
 * @param $form_state
 * @param $artwork
 *   The artwork object to edit, which may be brand new.
 */
function artwork_form($form, &$form_state, $artwork) {

  // Set the id and identify this as an artwork edit form.
  $form['#id'] = 'artwork-form';

  // Save the artwork for later, in case we need it.
  $form['#artwork'] = $artwork;
  $form_state['artwork'] = $artwork;
  
  // Common fields. We don't have many.
  $form['artwork_details'] = array(
    '#weight' => -100, 
  	'#prefix' => '<div id="ajax_markup_div">',
  	'title' => array(
      '#type' => 'textfield',
      '#title' => t('Artwork Title'),
      '#weight' => -10,
      '#required' => TRUE,
      '#default_value' => $artwork->title,
    ),
  	'price' => array(
      '#type' => 'textfield',
      '#title' => t('Price'),
      '#weight' => -9,
      '#required' => TRUE,
      '#default_value' => $artwork->max_price,
    ),
	'currency' => array(
	  '#type' => 'select',
      '#title' => t('Currency'),
      '#options' => array("USD" => "USD"),
	  '#weight' => -9,
	  '#default_value' => $artwork->currency,
	),
    'materials' => array(
      '#type' => 'textfield',
      '#title' => t('Materials'),
      '#weight' => -8,
      '#required' => TRUE,
      '#default_value' => $artwork->materials,
    ),
    'size' => array(
      '#type' => 'textfield',
      '#title' => t('Size'),
      '#weight' => -8,
      '#required' => TRUE,
      '#default_value' => $artwork->size,
    ),
    'category' => array(
      '#type' => 'textfield',
      '#title' => t('Category'),
      '#weight' => -7,
      '#required' => TRUE,
      '#default_value' => $artwork->category,
    ),
	'description' => array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#cols' => 60,
      '#rows' => 5,
      '#weight' => -6,
      '#resizable' => FALSE,
      '#required' => TRUE,
      '#default_value' => $artwork->description,
    ),
  	'short_description' => array(
      '#type' => 'textfield',
      '#title' => t('Short Description'),
      '#size' => 255,
      '#weight' => -5,
      '#required' => TRUE,
      '#default_value' => $artwork->short_description,  
    ),
    'tags' => array(
      '#type' => 'textfield',
      '#title' => t('Tags'),
      '#size' => 255,
      '#weight' => -5,
      '#required' => FALSE,
      '#default_value' => $artwork->tags,  
    ),
    'image_file_url' => array(
      '#type' => 'hidden',
    ),
    'etsy_id' => array(
      '#type' => 'textfield',
      '#title' => t('Etsy ID'),
      '#size' => 255,
      '#required' => FALSE,
      '#default_value' => $artwork->etsy_id,
    ),
    'ebay_id' => array(
      '#type' => 'textfield',
      '#title' => t('Ebay ID'),
      '#size' => 255,
      '#required' => FALSE,
      '#default_value' => $artwork->ebay_id,
    ),
    'stock_count' => array(
      '#type' => 'hidden',
    ),
    
    '#suffix' => '</div>',
  );
  $form['ebay_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Load data from Ebay, by pasting in a link here.'),
    '#weight' => 0,
  );

  $form['etsy_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Or load data from Etsy, by pasting in a link here.'),
    '#weight' => 0,
  );
    
  $form['artisan_id'] = array(
    '#type' => 'select',
    '#title' => t('Artisan'),
    '#options' => artisan_get_full_list(),
    '#weight' => -4,
    '#required' => TRUE,
    '#default_value' => $artwork->artisan_id,  
  );
  
  // Add the buttons.
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  
  $form['buttons']['load_product'] = array(
    '#value' => 'Load Etsy Product',
    '#type' => 'button',
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'artwork_add_etsy_item',
      'wrapper' => 'ajax_markup_div',
    ),
  );
  
  $form['buttons']['load_ebay_product'] = array(
    '#value' => 'Load Ebay Product',
    '#type' => 'button',
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'artwork_add_ebay_item',
      'wrapper' => 'ajax_markup_div',
    ),
  );
  
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('artwork_form_submit'),
  );
  
  if (!empty($artwork->item_id)) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete artworks'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('artwork_form_delete_submit'),
    );
  }

  $form['#validate'][] = 'artwork_form_validate';

  field_attach_form('artwork', $artwork, $form, $form_state);

  return $form;
}

function artwork_page_show_all_artworks() {
	return '<H1> All artworks are here. </H1>';
}

function artwork_add_etsy_item($form, $form_state) {
  
  if($res = preg_match('/http:\/\/www.etsy.com\/listing\/(.\d+)\/.*/i',  $_POST['etsy_link'], $matches) == 1) {
	$results = drupal_http_request('http://openapi.etsy.com/v2/listings/' . $matches[1] . '?api_key=6bh1geb40izfm8wnhag6wlij',array('Cache-Control'=>'no-cache'));
	if($results->code == 200) {
	  $item_details = drupal_json_decode($results->data);
	  $item_details = $item_details['results'][0];
	  
	  // Now request the listing of images.
	  $results = drupal_http_request('http://openapi.etsy.com/v2/listings/' . $matches[1] . '/images?api_key=6bh1geb40izfm8wnhag6wlij',array('Cache-Control'=>'no-cache'));
	  if($results->code == 200) {
	    $image_details = drupal_json_decode($results->data);
		
		$item_details['image_info'] = $image_details['results'];
		
		// Now we will fill in the form using data from Etsy.
		$form['artwork_details']['title']['#value'] = t($item_details['title']);
		$form['artwork_details']['price']['#value'] = $item_details['price'];
		$form['artwork_details']['materials']['#value'] = t($item_details['materials']);
		$form['artwork_details']['category']['#value'] = t($item_details['tags'][0]);
		$form['artwork_details']['description']['#value'] = t($item_details['description']);
		$form['artwork_details']['short_description']['#value'] = t(substr($item_details['description'],0,127));
		$form['artwork_details']['image_file_url']['#value'] = $item_details['image_info'][0]['url_fullxfull'];
		$form['artwork_details']['etsy_id']['#value'] = $item_details['listing_id'];
		$form['artwork_details']['stock_count']['#value'] = $item_details['quantity'];
		
		$form['artwork_details']['#suffix'] = theme('image',array('path' => $item_details['image_info'][0]['url_170x135'])) . "</div>";
      }
    }
  }
  
  return $form['artwork_details'];
}


function artwork_add_ebay_item($form, $form_state) {
  
  if($match_res = preg_match('/http:\/\/\w+.ebay.com\/itm\/.*\/(.\d+)\?.*/i',  $_POST['ebay_link'], $matches) == 1 || $match_res = preg_match('/http:\/\/\w+.ebay.com\/.*item\=(\d+)/i', $_POST['ebay_link'],$matches) == 1) {
	// Define global variables
	$s_endpoint = "http://open.api.ebay.com/shopping?";  // Shopping URL to call
	$cellColor = "bgcolor=\"#dfefff\"";  // Light blue background used for selected items 
	$m_endpoint = 'http://svcs.ebay.com/MerchandisingService?';  // Merchandising URL to call
	$appid = 'GlobeIn07-490a-488d-8a54-b4956d72221';  // You will need to supply your own AppID
	$responseEncoding = 'XML';  // Type of response we want back
	
	$details[] = 'Details';
	$details[] = 'Description';
	$details[] = 'ItemSpecifics';
	$details[] = 'Variations';
	
    // Construct the GetSingleItem call 
    $apicallb  = "$s_endpoint";
    $apicallb .= "callname=GetSingleItem";
    $apicallb .= "&version=563";
    $apicallb .= "&appid=$appid";
    $apicallb .= "&itemid=" . $matches[1];
	$apicallb .= '&includeselector=' . join(",",$details);
    $apicallb .= "&responseencoding=$responseEncoding";
	
    // Load the call and capture the document returned by eBay API
    $resp = simplexml_load_file($apicallb);
	$item_details = $resp->Item;

	//$item_details = $res->getItem();
		
	$description = html_entity_decode(str_replace("<br>","\n",(string)$item_details->Description), ENT_QUOTES, 'UTF-8');
	
	// Get Materials if available.
	foreach($item_details->Variations as $variation) {
	  if(isset($variation->Variation->VariationSpecifics->NameValueList)) {
		foreach($variation->Variation->VariationSpecifics->NameValueList as $specifics ){
		  if( $specifics->Name == 'Material') {
			$form['artwork_details']['materials']['#value'] = t((string)$specifics->Value);
		  }
	    }
	  }
	}
	
	$form['artwork_details']['title']['#value'] = t((string)$item_details->Title);//$res->title;// t($item_details['title']);
	$form['artwork_details']['description']['#value'] = $description;
	$form['artwork_details']['price']['#value'] = (string)$item_details->CurrentPrice;
	$form['artwork_details']['currency']['#value'] = (string)$item_details->CurrentPrice['currencyID'];
	
	$form['artwork_details']['category']['#value'] = t(array_pop(split(":",(string)$item_details->PrimaryCategoryName)));
	$form['artwork_details']['short_description']['#value'] = t(substr($description,0,127));
	$form['artwork_details']['image_file_url']['#value'] = (string)$item_details->PictureURL;
	$form['artwork_details']['ebay_id']['#value'] = (string)$item_details->ItemID;
	$form['artwork_details']['stock_count']['#value'] = (int)$item_details->Quantity;
	$form['artwork_details']['tags']['#value'] = '';
	
	$form['artwork_details']['#suffix'] = theme('image',array('path' => (string)$item_details->PictureURL)) . "</div>";
  }
  
  return $form['artwork_details'];
}

function artwork_form_validate($form, &$form_state) {
  $artwork = $form_state['artwork'];

  // Field validation.
  field_attach_form_validate('artwork', $artwork, $form, $form_state);
}


/**
* Caches a remote image url
*
* @param
*  $url a url to an image
*/
function artwork_cache_remote_image($url) {
  $external_image_path = file_default_scheme() . '://';
  $image = file_get_contents($url);

  $cut_url = str_ireplace("http://", "", $url);
  $cut_url = preg_replace("/^[^\/]*\//", "", $cut_url);
  $image_name = str_ireplace("/", "-", $cut_url);
  $tmp = explode('?',$image_name);
  $image_name = $tmp[0];
  $tmp = explode('.',$image_name);
  $image_name = md5($tmp[0]) . '.' . $tmp[1];
  dprint_r($image_name);
  $image_path = $external_image_path . '/' . $image_name;

  return file_save_data($image, $image_path, FILE_EXISTS_REPLACE);
}

function artwork_form_submit($form, &$form_state) {
  global $user;

  $artwork = &$form_state['artwork'];
  
  // Save the uploaded file from temp to permanent storage.
  if($form_state['values']['image_file_url'] != '') {
    $file_info = artwork_cache_remote_image($form_state['values']['image_file_url']);
	
	file_move($file_info,'public://',FILE_EXISTS_RENAME);
	$artwork->album_id = $file_info->fid;
  } else {
    //$file_info = file_load($form_state['field']['field_artwork_images']['und']['items'][0]['fid']);
	//$artwork->album_id = $file_info->fid;
  }
  
  $artwork->title = $form_state['values']['title'];
  $artwork->description = $form_state['values']['description'];
  $artwork->short_description = $form_state['values']['short_description'];
  $artwork->max_price = $form_state['values']['price'];
  $artwork->min_price = $form_state['values']['price'];
  $artwork->currency = $form_state['values']['currency'];
  $artwork->tags = $form_state['values']['tags'];
  $artwork->artisan_id = $form_state['values']['artisan_id'];
  $artwork->materials = $form_state['values']['materials'];
  $artwork->category = $form_state['values']['category'];
  $artwork->size = $form_state['values']['size'];
  $artwork->etsy_id = $form_state['values']['etsy_id'];
  $artwork->ebay_id = $form_state['values']['ebay_id'];
  $artwork->stock_count = $form_state['values']['stock_count'];
  
  if(empty($artwork->listing_date)) {
    $artwork->listing_date = REQUEST_TIME;
  }
  
  $artwork->last_updated = REQUEST_TIME;
  
  // Notify field widgets.
  field_attach_submit('artwork', $artwork, $form, $form_state);

  // Save the artwork.
  artwork_save($artwork);

  // Notify the user.
  drupal_set_message(t('artwork saved.'));

  $form_state['redirect'] = 'artwork/' . $artwork->item_id;
}


function artwork_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $artwork = $form['#artwork'];
  $form_state['redirect'] = array('artwork/' . $artwork->item_id . '/delete', array('query' => $destination));
}

/**
 * Displays an artwork.
 *
 * @param $artwork
 *   The artwork object to display.
 * @param $view_mode
 *   The view mode we want to display.
 */
function artwork_page_view($artwork, $view_mode = 'full') {
  // Remove previously built content, if exists.
  $artwork->content = array();

  if ($view_mode == 'teaser') {
    $artwork->content['title'] = array(
      '#markup' => filter_xss($artwork->title),
      '#weight' => -5,
    );
  }

  // Build fields content.
  field_attach_prepare_view('artwork', array($artwork->item_id => $artwork), $view_mode);
  entity_prepare_view('artwork', array($artwork->item_id => $artwork));
  $artwork->content += field_attach_view('artwork', $artwork, $view_mode);
  
  return $artwork->content;
}

/**
 * Form bulder; Asks for confirmation of artwork deletion.
 */
function artwork_delete_confirm($form, &$form_state, $artwork) {
  $form['#artwork'] = $artwork;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['item_id'] = array('#type' => 'value', '#value' => $artwork->item_id);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $artwork->title)),
    'artwork/' . $artwork->item_id,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Executes artwork deletion.
 */
function artwork_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $artwork = artwork_load($form_state['values']['item_id']);
    artwork_delete($form_state['values']['item_id']);
    watchdog('artwork', 'Deleted %title.', array('%title' => $artwork->title));

    drupal_set_message(t('%title has been deleted.', array('%title' => $artwork->title)));
  }

  $form_state['redirect'] = '<front>';
}
