<?php
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <ul class='artworks_list'>
    <?php foreach ($rows as $id => $row): ?>
      <li class="artworks_list_cell <?php print $classes_array[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  </ul>
<?php print $wrapper_suffix; ?>
