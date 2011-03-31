#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2011 United States Government as represented by
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
#	@file rt^3/src/ge/CMakeLists.txt
#
#	Origin -
#		TNO (Netherlands)
#		IABG mbH (Germany)
#
#########################################################################

IF(BRLCAD_VERSION_FOUND)
	SET(BRLCADVERSION_H_CONTENT
		"#define BRLCAD_LIB_MAJOR ${BRLCAD_MAJOR_VERSION}\n"
		"#define BRLCAD_LIB_MINOR ${BRLCAD_MINOR_VERSION}\n"
		"#define BRLCAD_LIB_PATCH ${BRLCAD_PATCH_VERSION}\n"
	)
	FILE(WRITE ${RT3_SOURCE_DIR}/include/brlcad/brlcadversion.h ${BRLCADVERSION_H_CONTENT})
ENDIF(BRLCAD_VERSION_FOUND)


if(EXISTS ${RT3_SOURCE_DIR}/include/brlcad/brlcadversion.h)

	#Set Include Dirs
	include_directories (
		${RT3_SOURCE_DIR}/include/brlcad
	    ${BRLCAD_INCLUDE_DIRS}
	)

	#set Source files
	set ( ge_SRCS
		GeometryEngine.cxx
		MinimalDatabase.cxx
		MinimalObject.cxx
		../coreInterface/Arb8.cpp
		../coreInterface/Combination.cpp
		../coreInterface/Cone.cpp
		../coreInterface/ConstDatabase.cpp
		../coreInterface/Database.cpp
		../coreInterface/Ellipsoid.cpp
		../coreInterface/EllipticalTorus.cpp
		../coreInterface/FileDatabase.cpp
		../coreInterface/globals.cpp
		../coreInterface/Halfspace.cpp
		../coreInterface/HyperbolicCylinder.cpp
		../coreInterface/Hyperboloid.cpp
		../coreInterface/MemoryDatabase.cpp
		../coreInterface/Object.cpp
		../coreInterface/ParabolicCylinder.cpp
		../coreInterface/Paraboloid.cpp
		../coreInterface/Particle.cpp
		../coreInterface/Torus.cpp
		../coreInterface/Unknown.cpp
	)

	IF(BUILD_SHARED_LIBS)
		add_library(ge SHARED ${ge_SRCS})
		install(TARGETS ge DESTINATION lib)
	ENDIF(BUILD_SHARED_LIBS)

	IF(BUILD_STATIC_LIBS)
		add_library(ge-static STATIC ${ge_SRCS})
		install(TARGETS ge-static DESTINATION lib)
	ENDIF(BUILD_STATIC_LIBS)
	
	SET(ge_inst_HDRS	
		${RT3_SOURCE_DIR}/include/GeometryEngine.h
		${RT3_SOURCE_DIR}/include/MinimalDatabase.h
		${RT3_SOURCE_DIR}/include/MinimalObject.h
		${RT3_SOURCE_DIR}/include/brlcad/Arb8.h
		${RT3_SOURCE_DIR}/include/brlcad/cicommon.h
		${RT3_SOURCE_DIR}/include/brlcad/Combination.h
		${RT3_SOURCE_DIR}/include/brlcad/Cone.h
		${RT3_SOURCE_DIR}/include/brlcad/ConstDatabase.h
		${RT3_SOURCE_DIR}/include/brlcad/Database.h
		${RT3_SOURCE_DIR}/include/brlcad/Ellipsoid.h
		${RT3_SOURCE_DIR}/include/brlcad/EllipticalTorus.h
		${RT3_SOURCE_DIR}/include/brlcad/FileDatabase.h
		${RT3_SOURCE_DIR}/include/brlcad/globals.h
		${RT3_SOURCE_DIR}/include/brlcad/Halfspace.h
		${RT3_SOURCE_DIR}/include/brlcad/HyperbolicCylinder.h
		${RT3_SOURCE_DIR}/include/brlcad/Hyperboloid.h
		${RT3_SOURCE_DIR}/include/brlcad/MemoryDatabase.h
		${RT3_SOURCE_DIR}/include/brlcad/Object.h
		${RT3_SOURCE_DIR}/include/brlcad/ParabolicCylinder.h
		${RT3_SOURCE_DIR}/include/brlcad/Paraboloid.h
		${RT3_SOURCE_DIR}/include/brlcad/Particle.h
		${RT3_SOURCE_DIR}/include/brlcad/Torus.h
		${RT3_SOURCE_DIR}/include/brlcad/Unknown.h
	)
	INSTALL(FILES ${ge_inst_HDRS} DESTINATION include/brlcad)
	TARGET_LINK_LIBRARIES(ge ${BRLCAD_BU_LIBRARY} ${BRLCAD_BN_LIBRARY} ${BRLCAD_RT_LIBRARY} ${BRLCAD_WDB_LIBRARY})

ELSE(EXISTS ${RT3_SOURCE_DIR}/include/brlcad/brlcadversion.h)
	MESSAGE(STATUS "\tConfiguration for 'ge'...  Omitted.")
ENDIF(EXISTS ${RT3_SOURCE_DIR}/include/brlcad/brlcadversion.h)
