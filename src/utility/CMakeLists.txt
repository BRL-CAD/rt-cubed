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
#	@file rt^3/src/GE/utility/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##           Configuring libUtility           ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

set(LIBUTILITY_SOURCES
	init.cxx
	Application.cxx
	Date.cxx
	Time.cxx
	Timer.cxx
	Utils.cxx
	Logger.cxx
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})

ADD_LIBRARY (utility SHARED ${LIBUTILITY_SOURCES})
TARGET_LINK_LIBRARIES(utility tds ${QT_LIBRARIES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
