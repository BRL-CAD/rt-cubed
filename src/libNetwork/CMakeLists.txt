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

PROJECT(LibNetwork)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS}  ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    ge
    job
    utility
    ${QT_LIBRARIES}
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(LIBNET_SOURCES
	NetPortal.cxx
	NetPortalManager.cxx
	NetMsgFactory.cxx
	NetMsgSubscriberRegistry.cxx
	NetMsg.cxx
	GenericOneStringMsg.cxx
	GenericOneByteMsg.cxx
	GenericTwoBytesMsg.cxx
	GenericFourBytesMsg.cxx
	GenericMultiByteMsg.cxx
	FailureMsg.cxx
	SuccessMsg.cxx
	RemHostNameSetMsg.cxx
	NewHostOnNetMsg.cxx
	GeometryReqMsg.cxx
	GeometryManifestMsg.cxx
	GeometryChunkMsg.cxx
)

QT4_WRAP_CPP(LIBNET_MOCCED_HEADERS
	${RT3_INCLUDE_DIR}/libNetwork/NetPortal.h
	${RT3_INCLUDE_DIR}/libNetwork/NetPortalManager.h
)

ADD_LIBRARY (network SHARED ${LIBNET_SOURCES} ${LIBNET_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(network ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")