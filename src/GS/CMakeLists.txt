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
#	@file rt^3/src/GS/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

RT3_PROJECT(gs)

#Set Include Dirs
RT3_PROJECT_ADD_INCLUDE_DIRS(
    ${QT_INCLUDE_DIR}
    ${BRLCAD_INC_DIRS}
)

#Set Libs
RT3_PROJECT_ADD_LIBS(
    ${QT_LIBRARIES}
    alf
    net
    utility
)

#set Source files
RT3_PROJECT_ADD_SOURCES (
	GeometryService.cxx
	DataManager.cxx
	DbObjectManifest.cxx
	DbObject.cxx
	GeometryProcessor.cxx
	Session.cxx
	SessionManager.cxx
	Account.cxx
	AccountManager.cxx
)

#Set INST Headers
RT3_PROJECT_ADD_INST_HEADERS(
	Session.h
	SessionManager.h
	Account.h
	AccountManager.h
	GeometryService.h
	DataManager.h
    IDataSource.h
	DbObject.h
)

#Set NOINST headers
RT3_PROJECT_ADD_NOINST_HEADERS(
	DbObjectManifest.h
	GeometryProcessor.h
)

#Set QT INST headers
RT3_PROJECT_ADD_QT_INST_HEADERS()

#Set QT NOINST headers
RT3_PROJECT_ADD_QT_NOINST_HEADERS()

#Build the project
RT3_PROJECT_BUILD_LIB()


##############
##############
##############

RT3_PROJECT(geoserv)

#Set Include Dirs
RT3_PROJECT_ADD_INCLUDE_DIRS(
    ${QT_INCLUDE_DIR}
)

#Set Libs
RT3_PROJECT_ADD_LIBS(
    ${QT_LIBRARIES}
    utility
    gs
    net
)

#set Source files
RT3_PROJECT_ADD_SOURCES (
	geoserv.cxx
)

#Set INST Headers
RT3_PROJECT_ADD_INST_HEADERS()

#Set NOINST headers
RT3_PROJECT_ADD_NOINST_HEADERS()

#Set QT INST headers
RT3_PROJECT_ADD_QT_INST_HEADERS()

#Set QT NOINST headers
RT3_PROJECT_ADD_QT_NOINST_HEADERS()

#Build the project
RT3_PROJECT_BUILD_EXE()

##############
##############
##############

RT3_PROJECT(geoclient)

#Set Include Dirs
RT3_PROJECT_ADD_INCLUDE_DIRS(
    ${QT_INCLUDE_DIR}
)

#Set Libs
RT3_PROJECT_ADD_LIBS(
    ${QT_LIBRARIES}
    utility
    gs
    net
)

#set Source files
RT3_PROJECT_ADD_SOURCES (
	geoclient.cxx
)

#Set INST Headers
RT3_PROJECT_ADD_INST_HEADERS()

#Set NOINST headers
RT3_PROJECT_ADD_NOINST_HEADERS()

#Set QT INST headers
RT3_PROJECT_ADD_QT_INST_HEADERS()

#Set QT NOINST headers
RT3_PROJECT_ADD_QT_NOINST_HEADERS()

#Build the project
RT3_PROJECT_BUILD_EXE()
