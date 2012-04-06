<?php
// $Id$

/**
 * @file
 * HTML for an item in the single blog's block listing.
 *
 * Available variables:
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - single-blog-block-item: The current template type, i.e., "theming hook".
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $title: A renderable array that that provides a title and link to the node.
 * - $name: Themed username of node author output from theme_username().
 *
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * Other variables:
 * The following variables are provided for contextual information.
 * - $node: Partial node object. Contains data that may not be safe.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $user: The user object of the node author.
 *
 * @see template_preprocess_single_blog_block_item()
 */
?>
<div class="artisan-profile-page <?php print $classes; ?>">
  <div class='artisan-list-photo'><a href="/artisan/<?php print $artisan_id; ?>"><img src="<?php print image_style_url('medium', $image_uri) ?>"></a></div>
  <div class='artisan-list-details'>
  <h4<?php print $title_attributes; ?>><a href="/artisan/<?php print $artisan_id; ?>"><?php print t('!artisan_name', array('!artisan_name' => $name)); ?></a></h4>
  <div class="artisan_description"><?php print $description; ?></div>
  <?php 
    dprint_r(isset($video_link));
	$video_link = "http://www.youtube.com/embed/VFv1iImmk7E";
    if(isset($video_link)) { 
      print '<div class="artisan_video"><iframe width="420" height="315" src="' . $video_link . '" frameborder="0" allowfullscreen></iframe></div>';
	}
  ?>
  </div>
</div>
