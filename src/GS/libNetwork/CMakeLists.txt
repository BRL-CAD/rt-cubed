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

PROJECT(GeometryService)

MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##           Configuring libNetwork           ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ")

SET(LIBNET_SOURCES
	NetPortal.cxx
	NetPortalManager.cxx
	netMsg/NetMsgFactory.cxx
	netMsg/NetMsg.cxx
	netMsg/GenericOneStringMsg.cxx
	netMsg/GenericOneByteMsg.cxx
	netMsg/GenericTwoBytesMsg.cxx
	netMsg/GenericFourBytesMsg.cxx
	netMsg/GenericMultiByteMsg.cxx
	netMsg/FailureMsg.cxx
	netMsg/SuccessMsg.cxx
	netMsg/RemHostNameSetMsg.cxx
	netMsg/NewHostOnNetMsg.cxx
	netMsg/GeometryReqMsg.cxx
	netMsg/GeometryManifestMsg.cxx
	netMsg/GeometryChunkMsg.cxx
)

QT4_WRAP_CPP(LIBNET_MOCCED_HEADERS
	${RT3_INCLUDE_DIR}/libNetwork/NetPortal.h
	${RT3_INCLUDE_DIR}/libNetwork/NetPortalManager.h
)

INCLUDE (${QT_USE_FILE})

IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

## Make the GS Library
ADD_LIBRARY (libNetwork SHARED ${LIBNET_SOURCES} ${LIBNET_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(libNetwork Utility ${QT_LIBRARIES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
