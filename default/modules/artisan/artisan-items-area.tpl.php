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
<div class="profile_artworks_wrapper">
<?php print '<div class="profile_section_title">' . t('Their Artworks') . '</div>'; ?>
<ul class="profile_artworks_list">
<?php foreach($items as $item) { ?>
  <?php print '<li class="profile_artwork_cell"><div class="profile_item_title">' . $item['title'] . '</div><img src="' . image_style_url('thumbnail', $item['image_url']) . '"><div class="proile_item_price">' . '$' . number_format($item['price'],2) . '</div></li>'; ?>
<?php } ?>
</ul>
</div>