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
#	@file rt^3/src/date/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring TimeDate Stamp          ##")
MESSAGE(STATUS "################################################\n")


set(TDS_SOURCES
	buildStamp.cxx
)

set(TDS_HEADERS
	buildStamp.h
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR}")

ADD_LIBRARY (tds SHARED ${TDS_HEADERS} ${TDS_SOURCES})
