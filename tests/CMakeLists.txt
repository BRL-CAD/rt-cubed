#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2011 United States Government as represented by
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
#	@file rt^3/tests/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################
message(status "out dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../tests-bin)

message(status "out dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ")

ADD_SUBDIRECTORY(./coreInterface)
ADD_SUBDIRECTORY(./libge)

