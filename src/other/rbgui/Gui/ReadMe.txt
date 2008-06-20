--------------------------------------------------------
INTRODUCTION
--------------------------------------------------------

This is the open source release of the Right Brain Games GUI (Version 0.1.3)

The Right Brain Games GUI is copyright (c) Right Brain Games Inc.
For more information, visit http://www.rightbraingames.com

--------------------------------------------------------
LICENSE INFORMATION
--------------------------------------------------------

The GUI is released under the terms of the LGPL license. The contents
of the license can be viewed here: http://www.gnu.org/licenses/lgpl.html

If you would like to use the GUI as a static library without the restrictions
of the LGPL, you may obtain a separate commercial license from us. Please
contact us via our website (http://www.rightbraingames.com/contact.php) or
send an email to shane@rightbraingames.com.

--------------------------------------------------------
OVERVIEW
--------------------------------------------------------

The GUI was originally designed for our custom game engine, Toi. Several
features were removed while porting it over to a more generic API. This is a
summary of the features removed:

* Support for multiple window layouts has not yet been ported. You can have
  multiple separate GUIs, but not multiple layouts within the GUIs. You can,
  of course, still have multiple windows.

* Window and widget persistance is only half implemented. You can save a widget
  to a file, but they cannot be loaded yet. This will soon be fixed.

* The GUI editor has not yet been ported. This will come at a later time.

* The original GUI code supported scaling windows relatively. This feature
  has been temporarily removed. It will soon be added back in.

Documentation is currently rather scarce. We will try to improve this over time.
For now you can view the Doxygen on our wesite, or see the Ogre sample application
for an example of how to use it.

--------------------------------------------------------
NEW IN RELEASE 0.1.3
--------------------------------------------------------

This release adds some new features and fixes some
annoying bugs that were found in version 0.1.2

* There was a bug in 0.1.2 that caused the Gui to render incorrectly
  in Ogre when shadow rendering was enabled. This has been fixed.

* You can change title of an attribute in an AttributeEditorWidget
  by calling the AttributeEditorWidget::updateTitle method.

* A new color option named 'WindowTitle' has been added to the theme
  file for overriding the color of window titles.

* You can create a generic question window with multiple choices using
  the GuiManager::createQuestionWindow method.

* Various minor bugs have been fixed.

--------------------------------------------------------
BUILDING
--------------------------------------------------------

You must have Visual C++ 8 to use the provided project file. To compile
the GUI you must download and install the Freetype 2 library, which can be
retrieved from here: http://www.freetype.org.

You must also download, compile and install Mocha, our small C++ types library.
It can be obtained from here: http://www.rightbraingames.com/tech.php.

If you want to compile the Ogre sample application and render support library,
you must download and compile Ogre. Ogre can be obtained from http://www.ogre3d.org.

When obtaining Ogre, use the latest version from CVS instead of the older versions.
This is important because the GUI depends on a patch that was recently submitted to
the Ogre code base.

You will also need to download and compile the Object Oriented Input System if you want
to compile the Ogre sample application. It can be obtained from
http://sourceforge.net/projects/wgois.

Before running the OgreSample application from the IDE, you may need to set the
working directory in the project settings. For Debug this is 'Bin/Debug'. For Release
this is 'Bin/Release'.

The project file contains several build configurations for building debug and
release mode DLLs, as well as debug and release modes for static linking. Please
contact us for licensing information if you would like to build the Gui for
static linking without the restrictions of the LGPL.

The GUI is designed to be cross platform, however only the Windows platform
is currently supported.

--------------------------------------------------------
SUPPORT
--------------------------------------------------------

We will do our best to improve documentation of the library over time.
Commercial support may be obtained for a fee upon request. Please contact us
for information via our website at: http://www.rightbraingames.com/contact.php
