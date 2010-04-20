#########################################################################
#
#	 BRL-CAD
#	
#	 Copyright (c) 1997-2010 United States Government as represented by
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
# 	@file /CMakeModules/ProjectPrinter.cmake
#
#   Common Print calls of a Project
#
#########################################################################


MESSAGE(STATUS "\tConfiguring '${PROJECT_NAME}'...")


IF(PROJ_INCLUDE_DIRS)
    MESSAGE(STATUS "\t\t'${PROJECT_NAME}' include dirs:")
    FOREACH (dir ${PROJ_INCLUDE_DIRS})
        MESSAGE(STATUS "\t\t\t${dir}")
    ENDFOREACH (dir)
ELSE(PROJ_INCLUDE_DIRS)
    MESSAGE(STATUS "\t\t'${PROJECT_NAME}' has no include dirs.")
ENDIF(PROJ_INCLUDE_DIRS)

IF(PROJ_LINK_LIBS)
    MESSAGE(STATUS "\t\t'${PROJECT_NAME}' linked libraries:")
    FOREACH (lib ${PROJ_LINK_LIBS})
        MESSAGE(STATUS "\t\t\t${lib}")
    ENDFOREACH (lib)
ELSE(PROJ_LINK_LIBS)
    MESSAGE(STATUS "\t\t'${PROJECT_NAME}' has no linked libraries.")
ENDIF(PROJ_LINK_LIBS)

