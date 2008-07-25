/*                  C O M M A N D S . H
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
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


#include "CommandInterpreter.h"

#include "Application.h"
#include "CameraManager.h"
#include "GeometryConversion.h"


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

  virtual void execute(std::vector<std::string>& args, CommandOutput& out) {
    if (args.size() > 0) {
      out.appendLine("Command doesn't accept arguments, ignoring");
    }
    
    Application::instance().quit();
  }
};


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

  virtual void execute(std::vector<std::string>& args , CommandOutput& out) {
    if (args.size() != 1) {
      out.appendLine("This command needs exactly one argument");
      return;
    }

    Logger::Level l = static_cast<Logger::Level>(0); // invalid level
    char firstChar = args[0][0];
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
};


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
      _argNames.push_back("mode");

      // setting wireframe by default
      Application::instance().setPolygonMode(Ogre::PM_WIREFRAME);
    }

  virtual void execute(std::vector<std::string>& args , CommandOutput& out) {
    if (args.size() != 1) {
      out.appendLine("This command needs exactly one argument");
      return;
    }

    if (args[0][0] == 's') {
      Application::instance().setPolygonMode(Ogre::PM_SOLID);
    } else if (args[0][0] == 'w') {
      Application::instance().setPolygonMode(Ogre::PM_WIREFRAME);
    } else if (args[0][0] == 'p') {
      Application::instance().setPolygonMode(Ogre::PM_POINTS);
    } else {
      out.appendLine("Mode not recognized");
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
    {
      _argNames.push_back("mode");
    }

  virtual void execute(std::vector<std::string>& args , CommandOutput& out) {
    if (args.size() > 0) {
      out.appendLine("Command doesn't accept arguments, ignoring");
    }

    CameraManager::instance().cycleCameraMode();
  }
};


/** @brief Create sample geometries.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandCreateSampleGeometry : public Command
{
public:
  CommandCreateSampleGeometry() :
    Command("create",
	    "Create a sample geometry",
	    "Argument is [tetrahedron|cube] (initial chars are enough)"),
    _sampleTetrahedron(50)
    {
      _argNames.push_back("shape");

      // creating an initial shape, for convenience while in initial
      // phases of development...
      Application::instance().addGeometry("tetrahedron", "TetrahedronMesh");
    }

  virtual void execute(std::vector<std::string>& args , CommandOutput& out) {
    if (args.size() != 1) {
      out.appendLine("This command needs exactly one argument");
      return;
    }

    if (args[0][0] == 't') {
      Application::instance().addGeometry("tetrahedron", "TetrahedronMesh");
    } else if (args[0][0] == 'c') {
      out.appendLine("Shape not implemented yet");
    } else {
      out.appendLine("Shape not recognized");
    }
  }

private:
  /** Sample geometry */
  SampleTetrahedron _sampleTetrahedron;
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

