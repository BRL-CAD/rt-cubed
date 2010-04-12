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
#	@file rt^3/src/alf/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##  Configuring Application Launch Framework  ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
     
PROJECT(alf)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

INCLUDE (${QT_USE_FILE})
SET (QT_USE_QTNETWORK TRUE)

set(ALF_SOURCES
    AppLauncher.cxx
    BaseApp.cxx
)

set(ALF_HEADERS

)

set(ALF_PREMOC_HEADERS
    
)

qt4_wrap_cpp(ALF_POSTMOC_HEADERS ${ALF_PREMOC_HEADERS})

ADD_LIBRARY (alf SHARED ${ALF_HEADERS} ${ALF_POSTMOC_HEADERS} ${ALF_SOURCES})
TARGET_LINK_LIBRARIES(alf utility ${QT_LIBRARIES} )


MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
