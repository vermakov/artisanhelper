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

$artisan_file_info = file_load($item['artisan']->album_id);
$artwork_file_info = file_load($item['artworks'][0]->album_id);
$artwork_file_info = file_load($item['artworks'][0]->album_id);

?>
<div class="artisan_item_cell">
  <div class="artisan_item_cell_artisan .clearfix">
    <img src="<?php print image_style_url('large', $artisan_file_info->uri) ?>">
    <div class="slider2_artisan_name"><?php print $item['artisan']->name; ?></div>
  </div>
  <div class="artisan_item_cell_item1 .clearfix">
    <img src="<?php print image_style_url('large', $artwork_file_info->uri) ?>">
  </div>
  <div class="artisan_item_cell_item2 .clearfix">
    <img src="<?php print image_style_url('large', $artwork_file_info->uri) ?>">
  </div>
</div>
