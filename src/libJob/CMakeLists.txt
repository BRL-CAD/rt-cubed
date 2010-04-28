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
#	@file rt^3/src/libJob/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

PROJECT(LibJob)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS 
    ${GLOBAL_INCLUDE_DIRS} 
    ${QT_INCLUDE_DIR}
    ${LIBUTILITY_PROJECT_DIR}
)

INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    utility
    ${QT_LIBRARIES}
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(LIBJOB_SOURCES
	AbstractJob.cxx
	JobManager.cxx
	JobScheduler.cxx
	JobWorker.cxx
	PrintToStdOutJob.cxx
)

QT4_WRAP_CPP(LIBJOB_MOCCED_HEADERS
)

ADD_LIBRARY (job SHARED ${LIBJOB_SOURCES} ${LIBJOB_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(job ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")
