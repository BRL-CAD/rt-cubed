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

RT3_PROJECT(net)

#Set Include Dirs
RT3_PROJECT_ADD_INCLUDE_DIRS(
    ${QT_INCLUDE_DIR}
    ${BRLCAD_INC_DIRS}
)

#Set Libs
RT3_PROJECT_ADD_LIBS(
    ge
    job
    utility
    event
    ${QT_LIBRARIES}
)

#set Source files
RT3_PROJECT_ADD_SOURCES (
	Portal.cxx
	PortalManager.cxx
	NetMsgFactory.cxx
	netMsg/NetMsg.cxx
	netMsg/TypeOnlyMsg.cxx
	netMsg/GenericOneStringMsg.cxx
	netMsg/GenericOneByteMsg.cxx
	netMsg/GenericTwoBytesMsg.cxx
	netMsg/GenericFourBytesMsg.cxx
	netMsg/GenericMultiByteMsg.cxx
	netMsg/FailureMsg.cxx
	netMsg/SuccessMsg.cxx
	netMsg/RemoteGSHostnameSetMsg.cxx
 	netMsg/NewSessionReqMsg.cxx
 	netMsg/SessionInfoMsg.cxx
	netMsg/NewHostOnNetMsg.cxx
	netMsg/GeometryReqMsg.cxx
	netMsg/GeometryManifestMsg.cxx
	netMsg/GeometryChunkMsg.cxx
)

#Set INST Headers
RT3_PROJECT_ADD_INST_HEADERS(
	Portal.h
	PortalManager.h
    NetMsgTypes.h
    INetMsgHandler.h
	NetMsgFactory.h
	NetMsg.h
	TypeOnlyMsg.h
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
RT3_PROJECT_ADD_NOINST_HEADERS()

#Set QT INST headers
RT3_PROJECT_ADD_QT_INST_HEADERS()

#Set QT NOINST headers
RT3_PROJECT_ADD_QT_NOINST_HEADERS()

#Build the project
RT3_PROJECT_BUILD_LIB()