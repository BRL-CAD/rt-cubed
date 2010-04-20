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

MESSAGE(STATUS "\tSearching for BRLCAD...")

#Attempt to get brlcad parameters.
FIND_PROGRAM(BRLCAD_CONFIGEXE brlcad-config)
IF(BRLCAD_CONFIGEXE)
	EXECUTE_PROCESS(COMMAND ${BRLCAD_CONFIGEXE} --version OUTPUT_VARIABLE BRLCAD_VERSION)
	EXECUTE_PROCESS(COMMAND ${BRLCAD_CONFIGEXE} --includedir OUTPUT_VARIABLE BRLCAD_INCLUDE_DIRS)
	EXECUTE_PROCESS(COMMAND ${BRLCAD_CONFIGEXE} --libdir OUTPUT_VARIABLE BRLCAD_LIBRARY_DIR)


	STRING(REGEX REPLACE "\n" "" BRLCAD_VERSION "${BRLCAD_VERSION}")
	STRING(REGEX REPLACE "\n" "" BRLCAD_INCLUDE_DIRS "${BRLCAD_INCLUDE_DIRS}")
	STRING(REGEX REPLACE "\n" "" BRLCAD_LIBRARY_DIR "${BRLCAD_LIBRARY_DIR}")

    MESSAGE(STATUS "\t\tDiscovered BRLCAD Version ${BRLCAD_VERSION}")

ELSE(BRLCAD_CONFIGEXE)
    RETURN()

ENDIF(BRLCAD_CONFIGEXE)

IF(NOT BRLCAD_INCLUDE_DIRS)
	MESSAGE(STATUS "\t\tCould not find brlcad in: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(NOT BRLCAD_INCLUDE_DIRS)


SET(BRLCAD_INCLUDE_DIRS ${BRLCAD_INCLUDE_DIRS}/brlcad ${BRLCAD_INCLUDE_DIRS} )
MESSAGE(STATUS "\t\tInclude dir: \t${BRLCAD_INCLUDE_DIRS}")

SET(BRLCAD_REQUIRED_LIBS regex bn bu dm fb ged optical orle pkg png rt sysv tclcad utahrle wdb openNURBS tcl85 tclstub85 tk85 tkpng tkstub85 BLT24 itcl34 itclstub34 itk34 itkstub34)

FOREACH (lib ${BRLCAD_REQUIRED_LIBS})
	FIND_LIBRARY( ${lib}_LIBRARY NAMES ${lib} PATHS ${LIB_SEARCH_PATHS} )
	
	IF(${lib}_LIBRARY)
	    SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} ${${lib}_LIBRARY} )
	    SET(BRLCAD_LIBS_FOUND ${BRLCAD_LIBS_FOUND} " ${lib}")
	ELSE(${lib}_LIBRARY)
	    SET(BRLCAD_LIBS_MISSING ${BRLCAD_LIBS_MISSING} " ${lib}")
	ENDIF(${lib}_LIBRARY)

ENDFOREACH (lib)

MESSAGE(STATUS "\t\tFound libs: \t${BRLCAD_LIBS_FOUND}")
MESSAGE(STATUS "\t\tLibs NOT Found: \t${BRLCAD_LIBS_MISSING}")

SET(BRLCAD_FOUND TRUE)