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

#include <OGRE/OgreSceneNode.h>

#include "Logger.h"
#include "CameraModes.h"

#include "CameraManager.h"


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
  // create camera modes that we'll use (default is the first
  // one, it will get in the front of the list)
  _cameraModeList.push_back(new CameraModeOrbital());
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

  notifyListenersCameraModeChanged(_cameraModeList.front());
}

void CameraManager::addListener(CameraListener* listener)
{
  // adding element, not checking for duplicates
  _listenerList.push_back(listener);
}

void CameraManager::removeListener(CameraListener* listener)
{
  // removing element, including duplicates
  _listenerList.remove(listener);
}

void CameraManager::notifyListenersCameraModeChanged(const CameraMode* mode)
{
  for (std::list<CameraListener*>::iterator it = _listenerList.begin();
       it != _listenerList.end();
       ++it) {
    (*it)->cameraModeChanged(mode);
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
