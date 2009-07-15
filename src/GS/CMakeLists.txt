#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2009 United States Government as represented by
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

PROJECT(GeometryService)

MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring GeometryService         ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ")


SET(GS_SOURCES
	AbstractPortal.cxx
	NetSockPortal.cxx
	AbstractPortalManager.cxx
	NetSockPortalManager.cxx
	GeometryService.cxx
	IntraAppPortal.cxx
	AbstractDbObjectSource.cxx
	SourceDiskLink.cxx
	SourceSvnLink.cxx
	DbObjectCache.cxx
	DbObjectManager.cxx
	DbObjectManifest.cxx
	Session.cxx
	SessionManager.cxx
	AccessManager.cxx
	NetMsgActionDefinitions/AbstractNetMsgActionDef.cxx
	NetMsgActionDefinitions/NetMsgActionDefManager.cxx
	NetMsgActionDefinitions/NewSessionNMAD.cxx
	Jobs/AbstractJob.cxx
	Jobs/CopyCacheToSvnJob.cxx
	Jobs/JobScheduler.cxx
	Jobs/NewSessionJob.cxx
	Jobs/CopyCacheToDiskJob.cxx
	Jobs/JobManager.cxx
	Jobs/JobWorker.cxx
	Jobs/NetMsgActionJob.cxx
	netMsg/GeometryManifestMsg.cxx
	netMsg/GeometryChunkMsg.cxx
	netMsg/GeometryReqMsg.cxx
	netMsg/NetMsg.cxx
	netMsg/RemHostNameSetFailMsg.cxx
	netMsg/RemHostNameSetMsg.cxx
)

QT4_WRAP_CPP(GS_MOCCED_HEADERS
	${RT3_INCLUDE_DIR}/GS/AbstractPortal.h
	${RT3_INCLUDE_DIR}/GS/NetSockPortal.h
	${RT3_INCLUDE_DIR}/GS/AbstractPortalManager.h
	${RT3_INCLUDE_DIR}/GS/NetSockPortalManager.h
)

INCLUDE (${QT_USE_FILE})

IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

## Make the GS Library
ADD_LIBRARY (gs SHARED ${GS_SOURCES} ${GS_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(gs ${QT_LIBRARIES})


## Make the GS phase 0 Executable.
ADD_EXECUTABLE(gsph0 gsph0.cxx)
TARGET_LINK_LIBRARIES(gsph0 ge gs ${QT_LIBRARIES})




MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")

