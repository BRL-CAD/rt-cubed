#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 2010 United States Government as represented by
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
#	@file rt^3/src/coreInterface/CMakeLists.txt
#
#	Origin -
#		TNO (Netherlands)
#		IABG mbH (Germany)
#
#########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##         Configuring  coreInterface         ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


IF(BRLCAD_VERSION)
	STRING(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" BRLCAD_MAJOR_VERSION "${BRLCAD_VERSION}")
	STRING(REGEX REPLACE "[0-9]+\\.([0-9]+)\\.[0-9]+" "\\1" BRLCAD_MINOR_VERSION "${BRLCAD_VERSION}")
	STRING(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" BRLCAD_PATCH_VERSION "${BRLCAD_VERSION}")

	SET(BRLCADVERSION_H_CONTENT
		"#define BRLCAD_LIB_MAJOR ${BRLCAD_MAJOR_VERSION}\n"
		"#define BRLCAD_LIB_MINOR ${BRLCAD_MINOR_VERSION}\n"
		"#define BRLCAD_LIB_PATCH ${BRLCAD_PATCH_VERSION}\n"
	)
	FILE(WRITE ${RT3_INCLUDE_DIR}/brlcad/brlcadversion.h ${BRLCADVERSION_H_CONTENT})
ENDIF(BRLCAD_VERSION)


if(EXISTS ${RT3_INCLUDE_DIR}/brlcad/brlcadversion.h)
	INCLUDE_DIRECTORIES(
		${RT3_INCLUDE_DIR}
		${BRLCAD_INCLUDE_DIRS}
		${BRLCAD_INCLUDE_DIRS}/brlcad
		${BRLCAD_INCLUDE_DIRS}/openNURBS
	)

	set(LIBCOREINTERFACE_SOURCES
		Arb8.cpp
		Cone.cpp
		Database.cpp
		EllipticalTorus.cpp
		globals.cpp
		MemoryDatabase.cpp
		Particle.cpp
		Torus.cpp
		Combination.cpp
		ConstDatabase.cpp
		Ellipsoid.cpp
		FileDatabase.cpp
		Halfspace.cpp
		Object.cpp
		Unknown.cpp
	)

	ADD_LIBRARY (coreInterface SHARED ${LIBCOREINTERFACE_SOURCES})

	MESSAGE(STATUS "Configuring Complete.")
ELSE(EXISTS ${RT3_INCLUDE_DIR}/brlcad/brlcadversion.h)
	MESSAGE(STATUS "Configuring Omitted.")
ENDIF(EXISTS ${RT3_INCLUDE_DIR}/brlcad/brlcadversion.h)

MESSAGE(STATUS "")
