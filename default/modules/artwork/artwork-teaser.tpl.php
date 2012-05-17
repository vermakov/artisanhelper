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
<div class="<?php print $classes; ?>">
  <div class="artwork-teaser-wrapper"><a href="<?php print $link_url; ?>">
  <div class="artwork_teaser_title"><?php print render($title); ?></div>
  <div class="artwork_teaser_pic"><img src="<?php print image_style_url('artwork_thumbnail', $image_uri) ?>"></div></a>
  <div class="artwork_teaser_name">by <a href="/artisan/<?php print $artisan_id; ?>"><?php print t('!username', array('!username' => $artisan_name)); ?></a></div>
  <div class="artwork_teaser_price"><?php print '$<div class="artwork_teaser_price_num">' . number_format($price,2) . '</div>USD'; ?></div>
  </div>
</div>
