/*                C A M E R A M A N A G E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by the
 * U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file CameraManager.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the Camera Manager class of 3D Geometry
 *	Editor (g3d).
 */

#include "CameraManager.h"

#include "Logger.h"
#include "CameraMode.h"
#include "CameraModeBlender.h"
//#include "CameraModeMGED.h"
#include "CameraModeOrbital.h"

#include <OGRE/OgreSceneNode.h>


/*******************************************************************************
 * CameraManager
 ******************************************************************************/
CameraManager* CameraManager::INSTANCE = 0;

CameraManager& CameraManager::instance()
{
  if (!INSTANCE)
    INSTANCE = new CameraManager();
  return *INSTANCE;
}

CameraManager::CameraManager()
{
  // create camera modes that we'll use (default is the first one, it
  // will get in the front of the list)
  _cameraModeList.push_back(new CameraModeBlender());
  //_cameraModeList.push_back(new CameraModeMGED());
  _cameraModeList.push_back(new CameraModeOrbital());

  const char* cameraModeName = _cameraModeList.front()->getName();
  Logger::logINFO("Default camera mode: '%s'", cameraModeName);

  // notify observers
  notify(CameraObserverEvent(CameraObserverEvent::MODE_CHANGED,
			     cameraModeName));
}

CameraMode& CameraManager::getActiveCameraMode()
{
  return *(_cameraModeList.front());
}

void CameraManager::updateCamera(Ogre::Camera* camera, double elapsedSeconds)
{
  getActiveCameraMode().updateCamera(camera, elapsedSeconds);
}

void CameraManager::cycleCameraMode()
{
  _cameraModeList.push_back(_cameraModeList.front());
  _cameraModeList.pop_front();

  const char* cameraModeName = _cameraModeList.front()->getName();
  Logger::logINFO("Camera mode switched to: '%s'", cameraModeName);

  // notify observers
  notify(CameraObserverEvent(CameraObserverEvent::MODE_CHANGED,
			     cameraModeName));
}

bool CameraManager::injectKeyPressed(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_C:
    cycleCameraMode();
    return true;
  default:
    return getActiveCameraMode().injectKeyPressed(keyCode);
  }
}

bool CameraManager::injectKeyReleased(OIS::KeyCode keyCode)
{
  return getActiveCameraMode().injectKeyReleased(keyCode);
}

bool CameraManager::injectMouseMotion(int x, int y)
{
  return getActiveCameraMode().injectMouseMotion(x, y);
}

bool CameraManager::injectMousePressed(OIS::MouseButtonID buttonId, int x, int y)
{
  return getActiveCameraMode().injectMousePressed(buttonId, x, y);
}

bool CameraManager::injectMouseReleased(OIS::MouseButtonID buttonId, int x, int y)
{
  return getActiveCameraMode().injectMouseReleased(buttonId, x, y);
}

bool CameraManager::injectMouseScrolled(CameraMode::Direction direction)
{
  return getActiveCameraMode().injectMouseScrolled(direction);
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
