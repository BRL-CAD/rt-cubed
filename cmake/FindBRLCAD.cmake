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


	STRING(REGEX REPLACE "\n" "" BRLCAD_VERSION "${BRLCAD_VERSION}")
	STRING(REGEX REPLACE "\n" "" BRLCAD_INCLUDE_DIRS "${BRLCAD_INCLUDE_DIRS}")
	STRING(REGEX REPLACE "\n" "" BRLCAD_LIBRARIES "${BRLCAD_LIBRARIES}")

    MESSAGE(STATUS "\t\tDiscovered BRLCAD Version ${BRLCAD_VERSION}")

ELSE(BRLCAD_CONFIGEXE)
    MESSAGE(STATUS "\t\tCould not discover BRLCAD Version.")
    #RETURN()
    #TODO need to make the BRLCAD version checking a requirement for coreInterface, but nothing else.
    #TODO figure out why brlcad-config isn't present on Windows.
ENDIF(BRLCAD_CONFIGEXE)


IF(NOT BRLCAD_INCLUDE_DIRS)
	MESSAGE(STATUS "\t\tCould not find brlcad in: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(NOT BRLCAD_INCLUDE_DIRS)


SET(BRLCAD_INCLUDE_DIRS ${BRLCAD_INCLUDE_DIRS} ${BRLCAD_INCLUDE_DIRS}/brlcad ${BRLCAD_INCLUDE_DIRS}/openNURBS)
MESSAGE(STATUS "\t\tInclude dir: \t${BRLCAD_INCLUDE_DIRS}")
MESSAGE(STATUS "\t\tLibs: \t${BRLCAD_LIBRARIES}")

SET(BRLCAD_FOUND TRUE)
