#########################################################################
#
#	 BRL-CAD
#	
#	 Copyright (c) 1997-2009 United States Government as represented by
#	 the U.S. Army Research Laboratory.
#	
#	 This library is free software; you can redistribute it and/or
#	 modify it under the terms of the GNU Lesser General Public License
#	 version 2.1 as published by the Free Software Foundation.
#	
#	 This library is distributed in the hope that it will be useful, but
#	 WITHOUT ANY WARRANTY; without even the implied warranty of
#	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	 Lesser General Public License for more details.
#	
#	 You should have received a copy of the GNU Lesser General Public
#	 License along with this file; see the file named COPYING for more
#	 information.
#	
#########################################################################
#	@file rt^3/src/coreInterface/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring Core Interface          ##")
MESSAGE(STATUS "################################################\n")

#INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${RT3_INCLUDE_DIR}/brlcad)
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${RT3_INCLUDE_DIR}/brlcad")

set(COREINTERFACE_SOURCES
	Arb8.cpp
	ConstDatabase.cpp
	FileDatabase.cpp
	MemoryDatabase.cpp
	Unknown.cpp
	Combination.cpp
	Database.cpp
	globals.cpp
	Object.cpp
	Cone.cpp
	Ellipsoid.cpp
	Halfspace.cpp
	Torus.cpp
)

set(COREINTERFACE_HEADERS
	${RT3_INCLUDE_DIR}/brlcad/common.h
	${RT3_INCLUDE_DIR}/brlcad/Arb8.h
	${RT3_INCLUDE_DIR}/brlcad/ConstDatabase.h
	${RT3_INCLUDE_DIR}/brlcad/FileDatabase.h
	${RT3_INCLUDE_DIR}/brlcad/MemoryDatabase.h
	${RT3_INCLUDE_DIR}/brlcad/Unknown.h
	${RT3_INCLUDE_DIR}/brlcad/Combination.h
	${RT3_INCLUDE_DIR}/brlcad/Database.h
	${RT3_INCLUDE_DIR}/brlcad/globals.h
	${RT3_INCLUDE_DIR}/brlcad/Object.h
	${RT3_INCLUDE_DIR}/brlcad/Cone.h
	${RT3_INCLUDE_DIR}/brlcad/Ellipsoid.h
	${RT3_INCLUDE_DIR}/brlcad/Halfspace.h
	${RT3_INCLUDE_DIR}/brlcad/Torus.h
)

ADD_LIBRARY (CoreInterface SHARED ${COREINTERFACE_HEADERS} ${COREINTERFACE_SOURCES})
TARGET_LINK_LIBRARIES(CoreInterface ${BRLCAD_LIBRARIES})
