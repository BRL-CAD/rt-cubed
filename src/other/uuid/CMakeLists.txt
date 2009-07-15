#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2009 United States Government as represented by
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
#	@file rt^3/src/other/uuid/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##               Configuring UUID             ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


set(UUID_SOURCES
	uuidcpp.cxx 
	uuid.c 
	uuid_cli.c 
	uuid_dce.c 
	uuid_mac.c 
	uuid_md5.c 
	uuid_prng.c 
	uuid_sha1.c 
	uuid_str.c 
	uuid_time.c 
	uuid_ui128.c 
	uuid_ui64.c
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} )
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR}")

ADD_LIBRARY (uuid SHARED ${UUID_SOURCES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
