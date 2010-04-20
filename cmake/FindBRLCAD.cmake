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
#	@file /cmake/FindBRLCAD.cmake
#
# 	Try to find brlcad libraries.
# 	Once done, this will define:
#
#  	BRLCAD_FOUND - system has BRLCAD
#  	BRLCAD_INCLUDE_DIRS - the BRLCAD include directories
#  	BRLCAD_LIBRARIES - link these to use the BRLCAD Libraries
#
#
#	The following paths are also defined:
#	bn_LIBRARY 
#	bu_LIBRARY 
#	dm_LIBRARY 
#	fb_LIBRARY 
#	ged_LIBRARY 
#	optical_LIBRARY 
#	orle_LIBRARY 
#	pkg_LIBRARY 
#	png_LIBRARY 
#	regex_LIBRARY 
#	rt_LIBRARY 
#	sysv_LIBRARY 
#	tclcad_LIBRARY 
#	utahrle_LIBRARY 
#	wdb_LIBRARY 
#	opennurbs_LIBRARY 
#	tcl85_LIBRARY 
#	tclstub85_LIBRARY 
#	tk85_LIBRARY 
#	tkpng_LIBRARY 
#	tkstub85_LIBRARY 
#	BLT24_LIBRARY 
#	itcl34_LIBRARY 
#	itclstub34_LIBRARY 
#	itk34_LIBRARY 
#	itkstub34_LIBRARY 
#
#
#	$Revision:  $
#	$Author:  $
#
#########################################################################

MESSAGE(STATUS "")
MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##           Searching for BRLCAD...          ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")



FIND_PROGRAM(BRLCAD_CONFIGEXE brlcad-config PATHS $ENV{BRLCAD_ROOT}/bin)

IF(BRLCAD_CONFIGEXE)
	EXEC_PROGRAM(${BRLCAD_CONFIGEXE} ARGS --version OUTPUT_VARIABLE BRLCAD_VERSION)
	EXEC_PROGRAM(${BRLCAD_CONFIGEXE} ARGS --includedir OUTPUT_VARIABLE BRLCAD_INCLUDE_DIRS)
	EXEC_PROGRAM(${BRLCAD_CONFIGEXE} ARGS --libdir OUTPUT_VARIABLE BRLCAD_LIBRARY_DIRS)

	SET(INCLUDE_SEARCH_PATHS
		${INCLUDE_SEARCH_PATHS}
		${BRLCAD_INCLUDE_DIRS}
	)

	SET(LIB_SEARCH_PATHS
		${LIB_SEARCH_PATHS}
		${BRLCAD_LIBRARY_DIRS}
	)
ENDIF(BRLCAD_CONFIGEXE)

# Include dirs
IF(NOT BRLCAD_INCLUDE_DIRS)
	FIND_PATH(BRLCAD_INCLUDE_DIRS
		NAMES brlcad/bu.h
		PATHS ${INCLUDE_SEARCH_PATHS}
	)
ENDIF(NOT BRLCAD_INCLUDE_DIRS)

IF(NOT BRLCAD_INCLUDE_DIRS)
	MESSAGE(STATUS "Could not find brlcad! ${BRLCAD_INCLUDE_DIRS}")
	MESSAGE(STATUS "\tSearched: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(NOT BRLCAD_INCLUDE_DIRS)

MESSAGE(STATUS "Found BRLCAD Include dir at: \t${BRLCAD_INCLUDE_DIRS}")


FOREACH (lib 
	bn   bu   dm   fb   ged   
	optical   orle   pkg   png   
	regex   rt   sysv   tclcad   
	utahrle   wdb   opennurbs   
	tcl85   tclstub85   tk85   
	tkpng   tkstub85  BLT24   
	itcl34   itclstub34   itk34   
	itkstub34
)
	FIND_LIBRARY( ${lib}_LIBRARY 	NAMES ${lib}	PATHS ${LIB_SEARCH_PATHS} )
	
	SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} ${${lib}_LIBRARY} )
	IF(NOT ${lib}_LIBRARY)
		MESSAGE(STATUS "Could not find: lib${lib} ")
	ELSE(NOT ${lib}_LIBRARY)
		MESSAGE(STATUS "Found: lib${lib} \t${${lib}}")
	ENDIF(NOT ${lib}_LIBRARY)


ENDFOREACH (lib)

