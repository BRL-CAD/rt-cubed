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
#  	BRLCAD_FOUND - system has BRL-CAD
#  	BRLCAD_VERSION - the BRL-CAD version string
#  	BRLCAD_INCLUDE_DIRS - the BRL-CAD include directories
#  	BRLCAD_LIBRARIES - link these to use the BRL-CAD Libraries
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
	EXECUTE_PROCESS(COMMAND ${BRLCAD_CONFIGEXE} --libs OUTPUT_VARIABLE BRLCAD_LIBRARIES)
	EXECUTE_PROCESS(COMMAND ${BRLCAD_CONFIGEXE} --libdir OUTPUT_VARIABLE BRLCAD_LIB_DIR)

	STRING(STRIP ${BRLCAD_VERSION} BRLCAD_VERSION)
	STRING(STRIP ${BRLCAD_INCLUDE_DIRS} BRLCAD_INCLUDE_DIRS)
	STRING(STRIP ${BRLCAD_LIBRARIES} BRLCAD_LIBRARIES)
	STRING(STRIP ${BRLCAD_LIB_DIR} BRLCAD_LIB_DIR)

ELSE(BRLCAD_CONFIGEXE)
    MESSAGE(STATUS "\t\tCould not locate 'brlcad-config'.")
    #RETURN()
    #TODO need to make the BRLCAD version checking a requirement for coreInterface, but nothing else.
    #TODO figure out why brlcad-config isn't present on Windows.
ENDIF(BRLCAD_CONFIGEXE)


IF(NOT BRLCAD_INCLUDE_DIRS)
	MESSAGE(STATUS "\t\tCould not find brlcad in: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(NOT BRLCAD_INCLUDE_DIRS)

#Add the additional include paths
SET(BRLCAD_INCLUDE_DIRS ${BRLCAD_INCLUDE_DIRS} ${BRLCAD_INCLUDE_DIRS}/brlcad )
SET(BRLCAD_INCLUDE_DIRS ${BRLCAD_INCLUDE_DIRS} ${BRLCAD_INCLUDE_DIRS}/openNURBS)


#Print status
MESSAGE(STATUS "\t\tDiscovered BRLCAD Version ${BRLCAD_VERSION}")
MESSAGE(STATUS "\t\tBRLCAD_INCLUDE_DIRS: \t${BRLCAD_INCLUDE_DIRS}")
MESSAGE(STATUS "\t\tBRLCAD_LIBRARIES: \t${BRLCAD_LIBRARIES}")
MESSAGE(STATUS "\t\tBRLCAD_LIB_DIR: \t${BRLCAD_LIB_DIR}")

SET(BRLCAD_FOUND TRUE)
