<?php // Corolla ?>
<div id="page-wrapper"><div id="page">

  <?php if ($menubar = render($page['menu_bar'])): ?>
    <div id="menu-bar-wrapper"><div class="container clearfix">
      <?php print $menubar; ?>
    </div></div>
  <?php endif; ?>

  <div id="header-wrapper"><div class="container clearfix">
    <header class="clearfix<?php print $linked_site_logo ? ' with-logo' : ''; ?>" role="banner">
      <div id="branding">
        <?php if ($linked_site_logo): ?>
          <div id="logo"><?php print $linked_site_logo; ?></div>
        <?php endif; ?>

        <?php if ($site_name || $site_slogan): ?>
          <hgroup<?php if (!$site_slogan && $hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>>
            <?php if ($site_name): ?>
              <h1 id="site-name"<?php if ($hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>><?php print $site_name; ?></h1>
            <?php endif; ?>
            <?php if ($site_slogan): ?>
              <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
            <?php endif; ?>
          </hgroup>
        <?php endif; ?>
      </div>

      <?php print render($page['header']); ?>

    </header>
  </div></div>

  <?php if ($page['three_33_first'] || $page['three_33_second'] || $page['three_33_third']): ?>
    <div id="top-panels-wrapper"><div class="container clearfix">
      <div class="three-3x33 gpanel clearfix">
        <?php print render($page['three_33_first']); ?>
        <?php print render($page['three_33_second']); ?>
        <?php print render($page['three_33_third']); ?>
      </div>
    </div></div>
  <?php endif; ?>


  <?php if ($page['four_first'] || $page['four_second'] || $page['four_third'] || $page['four_fourth']): ?>
    <div id="footer-panels-wrapper"><div class="container clearfix">
      <div class="four-4x25 gpanel clearfix">
        <?php print render($page['four_first']); ?>
        <?php print render($page['four_second']); ?>
        <?php print render($page['four_third']); ?>
        <?php print render($page['four_fourth']); ?>
      </div>
    </div></div>
  <?php endif; ?>

  <?php if ($page['tertiary_content']): ?>
    <div id="tertiary-content-wrapper"><div class="container clearfix">
      <?php print render($page['tertiary_content']); ?>
    </div></div>
  <?php endif; ?>

  <?php if ($page['footer']): ?>
    <div id="footer-wrapper"><div class="container clearfix">
      <footer class="clearfix" role="contentinfo">
        <?php print render($page['footer']); ?>
      </footer>
    </div></div>
  <?php endif; ?>

</div></div>
