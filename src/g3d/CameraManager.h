/*                C A M E R A M A N A G E R . H
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

/** @file CameraManager.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the Camera Manager class of 3D Geometry Editor
 *	(g3d).
 */

#ifndef __G3D_CAMERAMANAGER_H__
#define __G3D_CAMERAMANAGER_H__


#include "Observer.h"

#include <deque>
#include <list>


class CameraMode;
namespace Ogre {
  class Camera;
}


/**
 * @brief ObserverEvent for CameraManager
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CameraObserverEvent : public ObserverEvent
{
public:
  /** Action Identifier enumerator */
  enum ActionId { MODE_CHANGED = 1 };

  /** Action Identifier */
  const ActionId _actionId;
  /** Content of the event */
  const std::string _content;


  /** Default constructor */
  CameraObserverEvent(ActionId id, const std::string& content) :
    ObserverEvent("CameraObserverEvent"), _actionId(id), _content(content) { }
};


/** @brief Manager for the Camera.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 * 
 * Governs the camera: modes being used, etc.
 */
class CameraManager : public ObserverSubject
{
public:
  /** Singleton, access to the manager */
  static CameraManager& instance();

  /** Update the camera (acting upon active camera mode) */
  void updateCamera(Ogre::Camera* camera, double elapsedSeconds);

  /** Get the active camera mode */
  CameraMode& getActiveCameraMode();
  /** Cycle the camera mode to the next one */
  void cycleCameraMode();

private:
  /** Singleton instance */
  static CameraManager* INSTANCE;

  /** List of camera modes that we can use (front is the active
   * one) */
  std::deque<CameraMode*> _cameraModeList;


  /** Default constructor */
  CameraManager();

  /** Notify the listeners that the camera mode changed */
  void notifyListenersCameraModeChanged(const CameraMode* mode);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
