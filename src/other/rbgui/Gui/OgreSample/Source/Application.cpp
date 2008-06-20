/*
-----------------------------------------------------------------------------
This source file is part of the Right Brain Games GUI
For the latest info, see http://www.rightbraingames.com/

Copyright (c) 2000-2007 Right Brain Games Inc.

This sample program may be used in any way you want. It is not covered by the same
license as the Right Brain Games GUI.
-----------------------------------------------------------------------------
*/

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif

#include "Mocha/DataSection.h"
#include "Mocha/Stream.h"
#include "Mocha/Timer.h"

#include "RBGui/Exception.h"
#include "RBGui/WobbleWindowAnimator.h"
#include "RBGui/SimpleWindowFader.h"

#include "RBGui/OgreSupport/OgreTextureManager.h"
#include "RBGui/OgreSupport/OgreRenderQueueListener.h"
#include "RBGui/OgreSupport/OgreResourceManager.h"
#include "RBGui/OgreSupport/OgreBrush.h"

#include "RBGui/Widgets/DropSplineWidget.h"
#include "RBGui/Widgets/DropListWidget.h"
#include "RBGui/Widgets/ColorSelectWidget.h"
#include "RBGui/Widgets/AttributeEditWidget.h"
#include "RBGui/Widgets/ProgressWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"
#include "RBGui/Widgets/ImageWidget.h"
#include "RBGui/Widgets/MenuWidget.h"
#include "RBGui/Widgets/CheckWidget.h"
#include "RBGui/Widgets/OptionWidget.h"
#include "RBGui/Widgets/DirectoryListWidget.h"
#include "RBGui/Widgets/TextWidget.h"

#include "Application.h"

#include "RBGui/BrushCursorManager.h"

#if defined(WIN32)
#include "RBGui/Win32PlatformManager.h"
#include "RBGui/Win32CursorManager.h"
#elif defined(POSIX)
#include "RBGui/PosixPlatformManager.h"
#elif defined(MACOS)
#include "RBGui/MacOSPlatformManager.h"
#else
#error "No platform manager available"
#endif

//--------------------------------
class CustomStream : public Mocha::Stream
{
private:
	FILE* mFile;

public:
	CustomStream( const std::string& vName )
	{
		mFile = fopen( vName.c_str( ), "wb+" );
	}

	virtual ~CustomStream( )
	{
		fclose( mFile );
	}

	virtual size_t writeData( const void* vData, size_t vSize )
	{
		return fwrite( vData, 1, vSize, mFile );
	}

	virtual size_t readData( void* vData, size_t vSize ) const
	{
		return 0;
	}

	virtual void seek( size_t vPosition ) const
	{
		// ...
	}

	virtual size_t getSize( ) const
	{
		return 0;
	}

	virtual size_t getPosition( ) const
	{
		return ftell( mFile );
	}

	virtual bool getEndOfStream( ) const
	{
		return feof( mFile );
	}
};

//--------------------------------
class MouseListener : public OIS::MouseListener
{
private:
	Application& mOwner;

	Mocha::Vector2 mPrevPos;

	bool mFirst;

public:
	MouseListener( Application& vOwner )
		: mOwner( vOwner ), mFirst( true )
	{
		// ...
	}

	virtual bool mouseMoved( const OIS::MouseEvent& vEvent )
	{
		// Get absolute position

		Mocha::Vector2 abspos = Mocha::Vector2( (float)vEvent.state.X.abs, (float)vEvent.state.Y.abs );
		if ( mFirst )
		{
			mPrevPos = abspos;
			mFirst = false;
		}

		// Inject mouse scroll event

		if ( vEvent.state.Z.rel != 0 )
			mOwner.mGuiManager->injectMouseScrolled( (float)(vEvent.state.Z.rel / 120.0f), abspos );

		// Calculate relative position in pixels

		Mocha::Vector2 relpos = abspos - mPrevPos;
		mPrevPos = abspos;

		// Send event to gui

		mOwner.mGuiManager->injectMouseMotion( relpos, abspos );
		return true;
	}
	
	virtual bool mousePressed( const OIS::MouseEvent& vEvent, OIS::MouseButtonID id )
	{
		mOwner.mGuiManager->injectMousePressed( (RBGui::MouseButtonID)id, Mocha::Vector2( (float)vEvent.state.X.abs, (float)vEvent.state.Y.abs ) );
		return true;
	}

	virtual bool mouseReleased( const OIS::MouseEvent& vEvent, OIS::MouseButtonID id )
	{
		mOwner.mGuiManager->injectMouseReleased( (RBGui::MouseButtonID)id, Mocha::Vector2( (float)vEvent.state.X.abs, (float)vEvent.state.Y.abs ) );
		return true;
	}
};

//--------------------------------
class KeyListener : public OIS::KeyListener
{
private:
	Application& mOwner;

public:
	KeyListener( Application& vOwner )
		: mOwner( vOwner )
	{
		// ...
	}

	virtual bool keyPressed( const OIS::KeyEvent& vEvent )
	{
		// We don't need to translate key IDs because the Key IDs in the Gui are the same as OIS

		mOwner.mGuiManager->injectKeyPressed( (RBGui::KeyID)vEvent.key );
		return true;
	}
	
	virtual bool keyReleased( const OIS::KeyEvent& vEvent )
	{
		// We don't need to translate key IDs because the Key IDs in the Gui are the same as OIS

		mOwner.mGuiManager->injectKeyReleased( (RBGui::KeyID)vEvent.key );
		return true;
	}
};

//--------------------------------
class LostDeviceListener : public Ogre::RenderSystem::Listener 
{
public:
	virtual void eventOccurred( const Ogre::String& eventName, const Ogre::NameValuePairList *parameters )
	{
		// Redraw the Gui if the device has been lost

		if ( eventName == "DeviceLost" )
			RBGui::Core::Get( ).invalidate( );
	}
};

//--------------------------------
Application::Application( )
: mQuit( false ), mScene( 0 ), mViewport( 0 ), mRoot( 0 ), mWindow( 0 ), mMouse( 0 ), mProgress( 0 ),
  mKeyboard( 0 ), mCamera( 0 ), mMouseListener( 0 ), mKeyListener( 0 ), mInputManager( 0 ), mEntry( 0 )
{
	// ...
}

//--------------------------------
Application::~Application( )
{
	// Destroy input listeners

	delete mMouseListener;
	delete mKeyListener;

	// Destroy OIS

	if ( mInputManager )
	{
		// Destroy mouse

		if ( mMouse )
			mInputManager->destroyInputObject( mMouse );

		// Destory keyboard

		if ( mKeyboard )
			mInputManager->destroyInputObject( mKeyboard );

		// Destroy manager

		mInputManager->destroyInputSystem( mInputManager );
	}

	// Release Gui manager

	mGuiManager = 0;

	// Destroy Gui core

	mGuiCore = 0;

	// Shutdown Ogre

	delete mRoot;
}

//--------------------------------
void Application::addResourceLocations( )
{
	Ogre::ConfigFile config;
	config.load( "resources.cfg" );

	// Go through all sections & settings in the file

	Ogre::ConfigFile::SectionIterator seci = config.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while( seci.hasMoreElements( ) )
	{
		secName = seci.peekNextKey( );

		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;

			Ogre::ResourceGroupManager::getSingleton( ).addResourceLocation( archName, typeName, secName );
		}
	}
}

//--------------------------------
void Application::updateMouseWindowMetrics( )
{
	int x;
	int y;
	unsigned int  w;
	unsigned int  h;
	unsigned int  depth;
	mWindow->getMetrics( w, h, depth, x, y );

	const OIS::MouseState& state = mMouse->getMouseState( );
	state.width = (int)w;
	state.height = (int)h;
}

//--------------------------------
void Application::setupInput( )
{
	// Setup param list

	size_t data;
	mWindow->getCustomAttribute( "WINDOW", &data );

	std::ostringstream windowString;
	windowString << data;

	OIS::ParamList paramList;
	paramList.insert( std::make_pair( std::string( "WINDOW" ), windowString.str( ) ) );
	paramList.insert( std::make_pair( std::string( "w32_mouse" ), std::string( "DISCL_FOREGROUND" ) ) );
	paramList.insert( std::make_pair( std::string( "w32_mouse" ), std::string( "DISCL_NONEXCLUSIVE" ) ) );
	paramList.insert( std::make_pair( std::string( "w32_keyboard" ), std::string( "DISCL_FOREGROUND" ) ) );
	paramList.insert( std::make_pair( std::string( "w32_keyboard" ), std::string( "DISCL_NONEXCLUSIVE" ) ) );

	// Create input object using parameter list

	mInputManager = OIS::InputManager::createInputSystem( paramList );

	// Create the mouse

	mMouseListener = new MouseListener( *this );

	mMouse = static_cast<OIS::Mouse*>( mInputManager->createInputObject( OIS::OISMouse, true ) );
	mMouse->setEventCallback( mMouseListener );

	// Set mouse window metrics

	updateMouseWindowMetrics( );

	// Create the keyboard

	mKeyListener = new KeyListener( *this );

	mKeyboard = static_cast<OIS::Keyboard*>( mInputManager->createInputObject( OIS::OISKeyboard, true ) );
	mKeyboard->setEventCallback( mKeyListener );
}

//--------------------------------
void Application::browserResized( RBGui::GuiElement& vElement, const Mocha::ValueList& vData )
{
	RBGui::Window& win = static_cast<RBGui::Window&>( vElement );
	win.findWidget( "Editor" )->setSize( win.getClientRectangle( ).getSize( ) );
}

//--------------------------------
void Application::fileSelected( RBGui::GuiElement& vElement, const Mocha::ValueList& vData )
{
	mGuiManager->createMessageBox( "File Selected", "You selected: " + vData[0].getString( ) )->show( );
}

//--------------------------------
void Application::attributeChanged( RBGui::GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Get the name of the attribute

	const Mocha::String& name = vData[0].getAsString( );

	// Get the value of the attribute

	const Mocha::Value& value = vData[1];

	// Do something...

	if ( name == "BUTTON" )
		mGuiManager->createMessageBox( "Hooray!", "You clicked me!" )->show( );
	else if ( name == "SELECT_FILE" )
		mGuiManager->createFileSelectWindow( "Select File", ".", "ilk;dll", new RBGui::MemberGuiCallback<Application>( &Application::fileSelected, this ), RBGui::FILESELECTWINDOW_SAVE )->show( );
}

//--------------------------------
void Application::menuPicked( RBGui::GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Get the ID of the menu that was picked

	const Mocha::String& id = vData[0].getAsString( );

	// Do something with ID...

	if ( id == "FILE_QUIT" )
		quit( );
	else if ( id == "HELP_ABOUT" )
		mGuiManager->createMessageBox( "About", "Right Brain Games GUI\nOgre Sample Application\nVersion 1.0" )->show( );
}

//--------------------------------
void Application::initialize( )
{
	// Create ogre root

	mRoot = new Ogre::Root( "ogreplugins.cfg" );

	// Setup resource locations

	addResourceLocations( );

	// Try to initialize Ogre core

	if ( mRoot->showConfigDialog( ) )
		mWindow = mRoot->initialise( true, "Ogre Gui Sample" );
	else
		throw RBGui::Exception( "Unable to initialize Ogre" );

	// Create lost device listener

	Ogre::Root::getSingleton( ).getRenderSystem( )->addListener( new LostDeviceListener( ) );

	// Initialize resource groups

	Ogre::ResourceGroupManager::getSingleton( ).initialiseAllResourceGroups( );

	// Create scene

	mScene = mRoot->createSceneManager( "DefaultSceneManager", "Gui Sample Scene" );

	// Create camera

	mCamera = mScene->createCamera( "Gui Sample Camera" );

	// Add viewport

	mViewport = mWindow->addViewport( mCamera );
	mViewport->setBackgroundColour( Ogre::ColourValue( 0.4f, 0.4f, 0.4f, 1.0f ) );

	// Setup all the input stuff

	setupInput( );

	// Initialize the Gui. This adds all of the default widget factories

	RBGui::Initialize( );

	// Choose the platform and cursor manager to use

	Mocha::RefPointer<RBGui::PlatformManager> platformManager;
	Mocha::RefPointer<RBGui::CursorManager> cursorManager;

#if defined( WIN32 )
	platformManager = new RBGui::Win32PlatformManager( );
	cursorManager = new RBGui::Win32CursorManager( );
#elif defined( POSIX )
	platformManager = new RBGui::PosixPlatformManager( );
#elif defined( MACOSX )
	manager = new RBGui::MacOSPlatformManager( );
#endif

	// The following code can be used to setup a custom cursor

/*
	Mocha::RefPointer<RBGui::BrushCursorManager> bcursorManager = new RBGui::BrushCursorManager( );
	bcursorManager->setCursorType( RBGui::CURSOR_TEXT, "cursor_text.png", Mocha::Vector2( 3.0f, 8.0f ), RBGui::BRUSHBLEND_INVERT );
	bcursorManager->setCursorType( RBGui::CURSOR_RESIZE, "cursor_resize.png", Mocha::Vector2( 8.0f, 8.0f ) );
	bcursorManager->setCursorType( RBGui::CURSOR_DEFAULT, "cursor.png" ); 

	mGuiManager->setCursorManager( bcursorManager );
*/

	// Create the gui manager and set the default theme

	mGuiCore = new RBGui::Core( new RBGui::OgreTextureManager( ), platformManager, new RBGui::OgreResourceManager( ) );
	mGuiCore->getThemeManager( ).setDefaultTheme( "monochrome_grape.theme" );

	// Create a gui

	mGuiManager = mGuiCore->createGui( "My Gui", new RBGui::OgreBrush( mScene, mViewport ) );

	// Set the default window animator and fader for all created windows

	mGuiManager->setDefaultWindowAnimator( "Wobble" );
	mGuiManager->setDefaultWindowFader( "Simple" );

	// Set the cursor manager to use

	mGuiManager->setCursorManager( cursorManager );

	// Add a render queue listener to draw the GUI

	mScene->addRenderQueueListener( new RBGui::OgreRenderQueueListener( *mGuiManager ) );

	// Setup a test window

	Mocha::RefPointer<RBGui::Window> win = mGuiManager->createWindow( );
	win->setPosition( Mocha::Vector2( 64.0f, 64.0f ) );
	win->setSize( Mocha::Vector2( 300.0f, 300.0f ) );
	win->setText( "Wobbly Window" );
	win->show( );

	Mocha::RefPointer<RBGui::TextWidget> text = static_cast<RBGui::TextWidget*>( win->createWidget( "Text" ) );
	text->setPosition( Mocha::Vector2( 16.0f, 16.0f ) );
	text->setSize( Mocha::Vector2( 256.0f, 20.0f ) );
	text->setText( "Hello, world." );

	Mocha::RefPointer<RBGui::DropSplineWidget> spline = static_cast<RBGui::DropSplineWidget*>( win->createWidget( "DropSpline" ) );
	spline->setPosition( Mocha::Vector2( 16.0f, 64.0f ) );
	spline->setSize( Mocha::Vector2( 256.0f, 64.0f ) );

	Mocha::RefPointer<RBGui::CheckWidget> check = static_cast<RBGui::CheckWidget*>( win->createWidget( "Check" ) );
	check->setPosition( Mocha::Vector2( 16.0f, 140.0f ) );
	check->setSize( Mocha::Vector2( 256.0f, 25.0f ) );
	check->setText( "Check me!" );
	check->setChecked( true );

	Mocha::RefPointer<RBGui::OptionWidget> option = static_cast<RBGui::OptionWidget*>( win->createWidget( "Option" ) );
	option->setPosition( Mocha::Vector2( 16.0f, 160.0f ) );
	option->setSize( Mocha::Vector2( 256.0f, 25.0f ) );
	option->setText( "Select me!" );

	Mocha::RefPointer<RBGui::OptionWidget> option2 = static_cast<RBGui::OptionWidget*>( win->createWidget( "Option" ) );
	option2->setPosition( Mocha::Vector2( 16.0f, 180.0f ) );
	option2->setSize( Mocha::Vector2( 256.0f, 25.0f ) );
	option2->setText( "No, select me!" );

	// Create a menu along the top of the screen

	win = mGuiManager->createWindow( );
	win->setBorderVisible( false );
	win->setSize( Mocha::Vector2( mWindow->getWidth( ), 22.0f ) );
	win->show( );

	Mocha::RefPointer<RBGui::MenuWidget> menu = static_cast<RBGui::MenuWidget*>( win->createWidget( "Menu" ) );
	menu->setSize( win->getSize( ) );
	menu->setCallback( &Application::menuPicked, this );
	menu->addEntry( "File.Open File", "FILE_OPEN" );
	menu->addEntry( "File.-", "" );
	menu->addEntry( "File.Save File", "FILE_SAVE" );
	menu->addEntry( "File.Save File As", "FILE_SAVEAS" );
	menu->addEntry( "File.-", "" );
	menu->addEntry( "File.Quit", "FILE_QUIT" );

	menu->addEntry( "Another Menu.Another World", "FILE_ANOTHERWORLD" );
	menu->addEntry( "Another Menu.Another Time", "FILE_ANOTHERTIME" );
	menu->addEntry( "Another Menu.Another Time.In An Age Of Wonder", "FILE_INAGEOFWONDER" );
	menu->addEntry( "Another Menu.Another Time.This World Was Green And Good", "FILE_GREENANDGOOD" );
	menu->addEntry( "Another Menu.Another Time.This World Was Green And Good.Until The Crystal Cracked", "FILE_CRYSTAL" );

	menu->addEntry( "Help.About", "HELP_ABOUT" );

	// Create more test windows

	win = mGuiManager->createWindow( );
	win->setPosition( Mocha::Vector2( 128.0f, 128.0f ) );
	win->setSize( Mocha::Vector2( 300.0f, 400.0f ) );
	win->setText( "Another Test Window" );
	win->setCloseable( false );
	win->show( );

	// Set a callback so we know when the window is resized

	win->setCallback( &Application::browserResized, this, "Resized" );

	// Create an attribute edit widget

	RBGui::AttributeEditWidget* w = static_cast<RBGui::AttributeEditWidget*>( win->createWidget( "AttributeEdit" ) );
	w->setCallback( &Application::attributeChanged, this );
	w->setSize( win->getClientRectangle( ).getSize( ) );
	w->setName( "Editor" );

	// Fill in the attributes that can be edited
	// Each AttributeEntry has the following parameters:
	// Title, unique string ID, type, initial value
	// The string ID is used to identify the attribute when it changes in the callback
	// See Application::attributeChanged for an example of how to handle callbacks

	RBGui::AttributeMap m;
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "File Value", "FILE", "file|dll;exe" ) );
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "Float Value", "TEST1", "float", 4.0f ) );
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "Vector 2 Value", "TEST2", "vector2", 4.0f ) );
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "Vector 3 Value", "TEST3", "vector3", 4.0f ) );
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "Color Value", "COLOR", "color", 8.0f ) );
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "Push Me!", "BUTTON", "button" ) );
	m["Test Group 1"].push_back( RBGui::AttributeEntry( "Select File", "SELECT_FILE", "button" ) );
	m["Test Group 2"].push_back( RBGui::AttributeEntry( "Bool Value", "BOOL", "bool", false ) );
	m["Test Group 2"].push_back( RBGui::AttributeEntry( "Text Value", "TEXT", "text|multiline", "Hello!" ) );
	m["Test Group 2"].push_back( RBGui::AttributeEntry( "Int Value", "INT", "int", 20 ) );
	m["Test Group 2"].push_back( RBGui::AttributeEntry( "List Value", "LIST", "list|Entry 1|Entry 2|Entry 3|Entry 4", "Entry 2" ) );
	m["Test Group 2"].push_back( RBGui::AttributeEntry( "Spline Value", "SPLINE", "spline" ) );
	m["Test Group 2"].push_back( RBGui::AttributeEntry( "Slider Value", "SLIDER", "slider", 0.5f ) );

	w->setAttributes( m );
	w->updateAttribute( "BOOL", false );
	w->updateAttribute( "COLOR", Mocha::Color::Red );

	// Setup the handles of the spline attribute
	// This list could also have been passed in as the initial value for the attribute entry

	Mocha::ValueList v;
	v.push_back( Mocha::Vector2( 1, 0 ) );
	v.push_back( Mocha::Vector2( 1, 0.25 ) );
	v.push_back( Mocha::Vector2( 0, 0.75 ) );
	v.push_back( Mocha::Vector2( 0, 1 ) );

	w->updateAttribute( "SPLINE", v );

	// Test persistance

	Mocha::DataSection s;
	win->getRoot( )->save( s );

	Mocha::RefPointer<CustomStream> stream = new CustomStream( "test.widget" );
	s.write( *stream );
}

//--------------------------------
void Application::tick( float vDelta )
{
	// Pump message events

	Ogre::WindowEventUtilities::messagePump( );

	// Make sure mouse region is up to date

	updateMouseWindowMetrics( );

	// Capture mouse state

	if ( mMouse )
		mMouse->capture( );

	// Capture keyboard state

	if ( mKeyboard )
		mKeyboard->capture( );

	// Tick the gui manager

	mGuiManager->tick( vDelta );

	// Tell Ogre to render a frame. The GUI will get drawn as part of the Ogre render queue

	mRoot->renderOneFrame( );

	// If window was closed, we need to exit

	if ( mWindow->isClosed( ) )
		mQuit = true;
}

//--------------------------------
void Application::run( )
{
#ifdef WIN32
	// HACK!
	// This is required on Windows XP because of a bug that causes
	// timing to be wrong when more than one CPU is available.
	// This issue has been fixed in Vista.

	HANDLE id = GetCurrentThread( );

	DWORD pmask;
	DWORD psysmask;

	GetProcessAffinityMask( id, &pmask, &psysmask );
	DWORD res = SetThreadAffinityMask( id, 1 );
#endif

	// Run the main loop

	Mocha::Timer timer;
	while ( mQuit == false )
	{
		float delta = (float)timer.getDeltaSeconds( );
		tick( delta );
	}
}

//--------------------------------
void Application::quit( )
{
	mQuit = true;
}
