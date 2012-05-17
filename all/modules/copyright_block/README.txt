About "Copyright block"
=======================

Copyright block is a simple module to add a block to your Drupal installtion
to display the copyright holder. So this block will display something like

  "© My Drupal page 2011"

Installation
============

After you activated the module (at "admin/modules") you can put the block to
any region on your page (using "admin/structure/block").

Configuration
=============

The configuration is availabe after you added the block to your site. The
easiest way is to click the configure link next to the block. Alternatively
you can use this lengthy link:
"admin/structure/block/manage/copyright_block/copyright/configure"

You can configure two aspects of the block:

1. Copyright holder

The copyright holder is the name that will be displayed next to the copyright
year. By default it will show the name of your Drupal installation (configured
at "admin/config/system/site-information"). This can be overridden in the
configuration of this module.

The variable used to store the value is "copyright_block_copyrightholder"

2. Copyright starting year

The copyright starting year is the year the copyright starts. By default only
the current year will be shown. If the copyright started in the past you can
add this information. Adding the year will change the display to something
like

  "© My Drupal page 2008-2011"

The variable used to store the value is "copyright_block_inceptionyear"

You are also allowed to configure the display of the copyright block

1. Display template

This allows you to change the overall display of the copyright block. By
default it will display the holder followed by the year. This is done using
two simple replacements. The value "[holder] [year]" contains the placeholders

"[holder]": This will be replaced by the value of the copyright holder (see
above).

"[year]": This will be replaced by the current year (or by the year range if a
starting year is set)

2. Spacer template

You can configure the spacer template that will be used to seperate two years.
It will be used only if the copyright starting year is set and is different
from the current year.