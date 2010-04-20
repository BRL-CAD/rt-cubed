#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2010 United States Government as represented by
#	the U.S. Army Research Laboratory.
#	
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public License
#	version 2.1 as published by the Free Software Foundation.
#	
#	This library is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	Lesser General Public License for more details.
#	
#	You should have received a copy of the GNU Lesser General Public
#	License along with this file; see the file named COPYING for more
#	information.
#	
#########################################################################
#	@file rt^3/src/other/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##              Configuring  OIS              ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


PROJECT(OIS)

SET(OIS_HEADERS
	./includes/OISConfig.h
	./includes/OISEffect.h
	./includes/OISEvents.h
	./includes/OISException.h
	./includes/OISForceFeedback.h
	./includes/OISInputManager.h
	./includes/OISInterface.h
	./includes/OISJoyStick.h
	./includes/OISKeyboard.h
	./includes/OISMouse.h
	./includes/OISObject.h
	./includes/OISPrereqs.h
	./includes/OISFactoryCreator.h
	./includes/OIS.h
)

SET(OIS_SOURCES 
	./src/OISInputManager.cpp
	./src/OISObject.cpp
	./src/OISEffect.cpp
	./src/OISJoyStick.cpp
	./src/OISKeyboard.cpp
	./src/OISForceFeedback.cpp
	./src/OISException.cpp
)

IF(UNIX)
	SET(OIS_SOURCES 
		${OIS_SOURCES}
		./src/linux/EventHelpers.cpp
		./src/linux/LinuxInputManager.cpp
		./src/linux/LinuxJoyStickEvents.cpp
		./src/linux/LinuxForceFeedback.cpp
		./src/linux/LinuxKeyboard.cpp
		./src/linux/LinuxMouse.cpp
	)
ENDIF (UNIX)

IF(WIN32)
	SET(OIS_SOURCES 
		${OIS_SOURCES}
		./src/win32/Win32ForceFeedback.cpp
		./src/win32/Win32InputManager.cpp
		./src/win32/Win32JoyStick.cpp
		./src/win32/Win32Keyboard.cpp
		./src/win32/Win32Mouse.cpp
	)
ENDIF (WIN32)

IF(APPLE)
	SET(OIS_SOURCES 
		${OIS_SOURCES}
		./src/mac/MacHelpers.cpp
		./src/mac/MacHIDManager.cpp
		./src/mac/MacInputManager.cpp
		./src/mac/MacKeyboard.cpp
		./src/mac/MacMouse.cpp
	)
ENDIF (APPLE)


SET(OIS_INCLUDE_DIRS ${OIS_SOURCE_DIR}/includes)

INCLUDE_DIRECTORIES (${OIS_INCLUDE_DIRS} ${RT3_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${OIS_INCLUDE_DIRS}")

ADD_LIBRARY (ois SHARED ${OIS_HEADERS} ${OIS_SOURCES})
TARGET_LINK_LIBRARIES(ois X11)

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
