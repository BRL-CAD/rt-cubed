/*                  C O M M A N D S . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2010 United States Government as represented by
 * the U.S. Army Research Laboratory.
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

/** @file Commands.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of commands.
 */

#ifndef __G3D_COMMANDS_H__
#define __G3D_COMMANDS_H__


#include "Command.h"

#include <QtCore/QString>

#if 0
/** @brief Quit the application
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandQuit : public Command
{
public:
  CommandQuit() :
    Command("quit", "Quit the application", "")
    { }

  virtual QString execute(const QStringList &args) {
    if (args.length() > 0) {
      return CommandMessages::NO_ARGUMENTS;
    } else {
      // TODO
    }
    return "";
  }
};
#endif


/** @brief Set log message level.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandSetLogLevel : public Command
{
public:
  CommandSetLogLevel() :
    Command("loglevel",
	    "Set the log message level",
	    "Argument is first letter of Debug, Info, Warning, Error, Fatal")
    {
      _argNames.push_back("level");
    }

  virtual QString execute(const QStringList &args) {
    if (args.length() != 1) {
      return CommandMessages::ONE_ARGUMENT;
    } else {

      Logger::Level l = static_cast<Logger::Level>(0); // invalid level
      const QChar firstChar = args[0][0];
      if (firstChar == 'D') {
	l = Logger::DEBUG;
      } else if (firstChar == 'I') {
	l = Logger::INFO;
      } else if (firstChar == 'W') {
	l = Logger::WARNING;
      } else if (firstChar == 'E') {
	l = Logger::ERROR;
      } else if (firstChar == 'F') {
	l = Logger::FATAL;
      }

      Logger::instance().setLevelFilter(l);
    }
    return "";
  }
};

#if 0

/** @brief Set Polygon mode.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandSetPolygonMode : public Command
{
public:
  CommandSetPolygonMode() :
    Command("polygonmode",
	    "Set the polygon mode",
	    "Argument is [solid|wireframe|points] (initial chars are enough)")
    {
      _argNames += ("mode");

      // setting wireframe by default
      Application::instance().setPolygonMode(Ogre::PM_WIREFRAME);
    }

  virtual QString execute(const QStringList &args) {
    if (args.length() != 1) {
      return CommandMessages::ONE_ARGUMENT;
      return;
    } else {
      if (args[0][0] == 's') {
	Application::instance().setPolygonMode(Ogre::PM_SOLID);
      } else if (args[0][0] == 'w') {
	Application::instance().setPolygonMode(Ogre::PM_WIREFRAME);
      } else if (args[0][0] == 'p') {
	Application::instance().setPolygonMode(Ogre::PM_POINTS);
      } else {
	return "Mode not recognized";
      }
      return "";
    }
  }
};


/** @brief Set Camera projection type.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandSetCameraProjectionType : public Command
{
public:
  CommandSetCameraProjectionType() :
    Command("projection",
	    "Set camera projection type",
	    "Argument is [orthogonal|perspective] (initial chars are enough)")
    {
      _argNames.push_back("type");
    }

  virtual QString execute(const QStringList &args) {
    if (args.length() != 1) {
      output.appendLine(CommandMessages::ONE_ARGUMENT);
      return;
    } else {
      char firstChar = args[0][0];
      if (firstChar == 'o') {
	CameraManager::instance().setProjectionOrthogonal(true);
      } else {
	CameraManager::instance().setProjectionOrthogonal(false);
      }
      return "";
    }
  }
};


/** @brief Cycle Camera mode.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandCycleCameraMode : public Command
{
public:
  CommandCycleCameraMode() :
    Command("cyclecam", "Cycle the camera mode", "")
    { }

  virtual QString execute(const QStringList &args) {
    if (!args.empty()) {
      return CommandMessages::NO_ARGUMENTS;
    } else {
      CameraManager::instance().cycleCameraMode();
    }
    return "";
  }
};

#endif // #if 0

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

