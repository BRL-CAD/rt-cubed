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
#	@file rt^3/src/libNetwork/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

RT3_PROJECT(network)

#Set Include Dirs
RT3_PROJECT_ADD_INCLUDE_DIRS(
    ${QT_INCLUDE_DIR}
)

#Set Libs
RT3_PROJECT_ADD_LIBS(
    ge
    job
    utility
    ${QT_LIBRARIES}
)

#set Source files
RT3_PROJECT_ADD_SOURCES (
	NetPortal.cxx
	NetPortalManager.cxx
	NetMsgFactory.cxx
	NetMsg.cxx
	GenericOneStringMsg.cxx
	GenericOneByteMsg.cxx
	GenericTwoBytesMsg.cxx
	GenericFourBytesMsg.cxx
	GenericMultiByteMsg.cxx
	FailureMsg.cxx
	SuccessMsg.cxx
	RemoteGSHostnameSetMsg.cxx
    NewSessionReqMsg.cxx
    SessionInfoMsg.cxx
	NewHostOnNetMsg.cxx
	GeometryReqMsg.cxx
	GeometryManifestMsg.cxx
	GeometryChunkMsg.cxx
	Gateway.cxx
)

#Set INST Headers
RT3_PROJECT_ADD_INST_HEADERS(
    INetMsgHandler.h
	NetMsgFactory.h
	NetMsg.h
	RemoteGSHostnameSetMsg.h
	GenericOneStringMsg.h
	GenericOneByteMsg.h
	GenericTwoBytesMsg.h
	GenericFourBytesMsg.h
	GenericMultiByteMsg.h
	FailureMsg.h
	SuccessMsg.h
    NewSessionReqMsg.h
    SessionInfoMsg.h
	NewHostOnNetMsg.h
	GeometryReqMsg.h
	GeometryManifestMsg.h
	GeometryChunkMsg.h
)

#Set NOINST headers
RT3_PROJECT_ADD_NOINST_HEADERS(
	Gateway.h
)

#Set QT INST headers
RT3_PROJECT_ADD_QT_INST_HEADERS(
	NetPortal.h
	NetPortalManager.h
)

#Set QT NOINST headers
RT3_PROJECT_ADD_QT_NOINST_HEADERS()

#Build the project
RT3_PROJECT_BUILD_LIB()