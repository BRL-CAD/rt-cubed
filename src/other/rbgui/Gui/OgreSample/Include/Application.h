/*
-----------------------------------------------------------------------------
This source file is part of the Right Brain Games GUI
For the latest info, see http://www.rightbraingames.com/

Copyright (c) 2000-2007 Right Brain Games Inc.

This sample program may be used in any way you want. It is not covered by the same
license as the Right Brain Games GUI.
-----------------------------------------------------------------------------
*/

#ifndef GUI_OGRESAMPLEAPP_H
#define GUI_OGRESAMPLEAPP_H

#include "Ogre.h"
#include "OIS.h"

#include "RBGui/Core.h"

//#include "RBGui/Widgets/BrowserWidget.h"
#include "RBGui/Widgets/ProgressWidget.h"
#include "RBGui/Widgets/TextEntryWidget.h"

class MouseListener;
class KeyListener;

class Application
{

friend class LostDeviceListener;
friend class MouseListener;
friend class KeyListener;

private:
	Mocha::RefPointer<RBGui::Core> mGuiCore;

	Mocha::RefPointer<RBGui::GuiManager> mGuiManager;

	RBGui::ProgressWidget* mProgress;

	RBGui::TextEntryWidget* mEntry;

	MouseListener* mMouseListener;

	KeyListener* mKeyListener;

	OIS::Mouse* mMouse;

	OIS::Keyboard* mKeyboard;

	OIS::InputManager* mInputManager;

	Ogre::SceneManager* mScene;

	Ogre::RenderWindow* mWindow;

	Ogre::Viewport* mViewport;

	Ogre::Camera* mCamera;

	Ogre::Root* mRoot;

	bool mQuit;

	void addResourceLocations( );

	void setupInput( );

	void fileSelected( RBGui::GuiElement& vElement, const Mocha::ValueList& vData );

	void browserResized( RBGui::GuiElement& vElement, const Mocha::ValueList& vData );

	void attributeChanged( RBGui::GuiElement& vElement, const Mocha::ValueList& vData );

	void menuPicked( RBGui::GuiElement& vElement, const Mocha::ValueList& vData );

	void updateMouseWindowMetrics( );

public:
	Application( );

	~Application( );

	void initialize( );

	void tick( float vDelta );

	void run( );

	void quit( );
};

#endif
