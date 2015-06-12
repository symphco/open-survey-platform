; $Id$
=======================
Arrange Fields
(For Drupal 7)
=======================
Richard Peacock (richard@richardpeacock.com)

This module lets you drag-and-drop the fields of any content type, Webform,
or almost any other form in Drupal into the 
positions you would like for editing. This makes it super simple to have forms 
with inline fields, which you can change at any point. Tab indexing is also respected, 
so no matter how you arrange the fields, the users can still tab through them easily.

You can also add arbitrary bits of markup to the form as well, including extra labels,
images, etc.

=======================
Restrictions
=======================
 - This module does not work so well with fields with "unlimited" as their number of
   values.
 
 - Multi-page forms are not currently supported.
 
 - Fields within fieldsets cannot be arranged.  But, the fieldset itself
   can be re-arranged.
   
 - jQuery is used to properly specify the height of the container 
   div on the node/edit page, after you have arranged fields. As such, 
   the person editing the form will need javascript enabled in order for it 
   to show up correctly. (If anyone out there knows a better way to do this, 
   please open an issue!)
 
 - Field positions will not change the node view page for the created 
   content. That information will still be displayed the traditional 
   way (straight down the page).

 - This module doesn't try to work on Webform's submissions pages.  It just
   uses the default display for those.
   
   
======================
Directions
======================

- Unpack the module files into /sites/all/modules/arrange_fields.

- Visit your modules page in Drupal and enable the module.

- Visit your permissions and give authorized users the
  "administer arrange fields" permission, if desired.  (Otherwise, only the
  admin user will be able to use it).

- To begin arranging fields just visit admin/config/arrange-fields to see a main menu page.
  Visit the Settings tab on that page to add arbitrary form_id's to the list which
  you can arrange.
  OR...
  - For Drupal content types:
    - visit Administer -> Content Types (the link
      is at the top of the page, as a tab).  You can also select "manage fields" 
      for a content type, and then there will be a new tab at the top of 
      this page as well.
  - For Webform:
    - Begin editing a new or existing webform.  There will be a subtab at the top
      of the page that says "Arrange fields".  It should be next to the "Form components"
      subtab.


======================
Notes
======================
Included icon(s) are from the "mini" pack at famfamfam.com.