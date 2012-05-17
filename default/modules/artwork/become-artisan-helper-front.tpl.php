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
<div class="<?php print $classes; ?> clearfix" style="width:1200px">
<table width="100%">
<tr><td>
<div id="become_artisan_helper" class="clearfix" style="float:left;display:inline"><a href="/join"><img src="/sites/default/files/become_artisan_helper.jpg"></a></div>
</td><td style="vertical-align:top">
<div id="slogan_phrase" class="clearfix" style="float:left;margin:20px 0 0 40px;display:none">
<div style="font-size:40pt;color:black;">Discover.</div><div style="margin-left:80px;font-size:40pt;color:#E25401;">Connect.</div><div style="margin-left:160px;display:inline;font-size:40pt;color:black">Globe</div><div style="display:inline;font-size:40pt;color:#E25401">In.</div>
</div>
<div id="about_exerpt" class="clearfix" style="float:left;margin:0;font-size:20pt;display:inline">
All goods on <B>Globe<span style="color:#E25401">In</span></B> are handmade by individual artisans in developing countries. By buying from these artisans, you are bringing diverse culture, the artisan's creations and part of their soul into your house.<br>
<a href="/about">Read more about us >></a>  
</div>
</td></tr>
</table>
</div>
