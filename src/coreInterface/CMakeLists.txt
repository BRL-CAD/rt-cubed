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
#	@file rt^3/src/coreInterface/CMakeLists.txt
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
		${TCL_INCLUDE_PATH}
	)

	#set Source files
	set ( coreinterface_SRCS
		Arb8.cpp
		BagOfTriangles.cpp
		Combination.cpp
		Cone.cpp
		ConstDatabase.cpp
		Database.cpp
		Ellipsoid.cpp
		EllipticalTorus.cpp
		FileDatabase.cpp
		globals.cpp
		Halfspace.cpp
		HyperbolicCylinder.cpp
		Hyperboloid.cpp
		MemoryDatabase.cpp
		NonManifoldGeometry.cpp
		Object.cpp
		ParabolicCylinder.cpp
		Paraboloid.cpp
		Particle.cpp
		Pipe.cpp
		Sketch.cpp
		Sphere.cpp
		Torus.cpp
		Unknown.cpp
	)

	IF(BUILD_SHARED_LIBS)
		add_library(coreinterface SHARED ${coreinterface_SRCS})
#		target_link_libraries(coreinterface ${})
#		set_target_properties(coreinterface PROPERTIES PREFIX "")
		install(TARGETS coreinterface DESTINATION lib)
	ENDIF(BUILD_SHARED_LIBS)

	IF(BUILD_STATIC_LIBS)
		add_library(coreinterface-static STATIC ${coreinterface_SRCS})
#		target_link_libraries(coreinterface-static ${})
		IF(NOT WIN32)
#			set_target_properties(coreinterface-static PROPERTIES PREFIX "")
#			set_target_properties(coreinterface-static PROPERTIES OUTPUT_NAME "libcoreinterface")
		ELSE(NOT WIN32)
#			set_target_properties(coreinterface-static PROPERTIES PREFIX "lib")
		ENDIF(NOT WIN32)
		install(TARGETS coreinterface-static DESTINATION lib)
	ENDIF(BUILD_STATIC_LIBS)

	SET(coreinterface_inst_HDRS
		${RT3_SOURCE_DIR}/include/brlcad/Arb8.h
		${RT3_SOURCE_DIR}/include/brlcad/BagOfTriangles.h
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
		${RT3_SOURCE_DIR}/include/brlcad/NonManifoldGeometry.h
		${RT3_SOURCE_DIR}/include/brlcad/Object.h
		${RT3_SOURCE_DIR}/include/brlcad/ParabolicCylinder.h
		${RT3_SOURCE_DIR}/include/brlcad/Paraboloid.h
		${RT3_SOURCE_DIR}/include/brlcad/Particle.h
		${RT3_SOURCE_DIR}/include/brlcad/Sketch.h
		${RT3_SOURCE_DIR}/include/brlcad/Sphere.h
		${RT3_SOURCE_DIR}/include/brlcad/Torus.h
		${RT3_SOURCE_DIR}/include/brlcad/Unknown.h
	)
	INSTALL(FILES ${coreinterface_inst_HDRS} DESTINATION include/brlcad)
	TARGET_LINK_LIBRARIES(coreinterface ${BRLCAD_BU_LIBRARY} ${BRLCAD_BN_LIBRARY} ${BRLCAD_RT_LIBRARY} ${BRLCAD_WDB_LIBRARY})

ELSE(EXISTS ${RT3_SOURCE_DIR}/include/brlcad/brlcadversion.h)
	MESSAGE(STATUS "\tConfiguration for 'coreInterface'...  Omitted.")
ENDIF(EXISTS ${RT3_SOURCE_DIR}/include/brlcad/brlcadversion.h)
