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


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring GeometryService         ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


set(GS_SOURCES
	GeometryService.cxx
	IntraAppPortal.cxx
	AbstractPortal.cxx
	AbstractPortalManager.cxx
	NetSockPortal.cxx
	NetSockPortalManager.cxx
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

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

ADD_LIBRARY (gs SHARED ${GS_SOURCES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")

