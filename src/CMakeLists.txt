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
#	@file rt^3/src/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


#Build 'others' first
ADD_SUBDIRECTORY(./other/)
ADD_SUBDIRECTORY(./coreInterface)
ADD_SUBDIRECTORY(./date)
ADD_SUBDIRECTORY(./GE)
ADD_SUBDIRECTORY(./GS)
ADD_SUBDIRECTORY(./iBME)
ADD_SUBDIRECTORY(./alf)
ADD_SUBDIRECTORY(./libUtility)
ADD_SUBDIRECTORY(./adminpanel)

