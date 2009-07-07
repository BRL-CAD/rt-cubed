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
#	@file /cmake/FindBRLCAD.cmake
#
# 	Try to find brlcad libraries.
# 	Once done, this will define:
#
#  	BRLCAD_FOUND - system has BRLCAD
#  	BRLCAD_INCLUDE_DIRS - the BRLCAD include directories
#  	BRLCAD_LIBRARIES - link these to use the BRLCAD Libraries
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
#
#	opennurbs_LIBRARY 
#
#	tcl85_LIBRARY 
#	tclstub85_LIBRARY 
#	tk85_LIBRARY 
#	tkimg_LIBRARY 
#	tkstub85_LIBRARY 
#
#	BLT24_LIBRARY 
#	itcl34_LIBRARY 
#	itclstub34_LIBRARY 
#	itk34_LIBRARY 
#	itkstub34_LIBRARY 
#
#	
#	
#	$Revision:  $
#	$Author:  $
#
#########################################################################

MESSAGE(STATUS "\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##           Searching for BRLCAD...          ##")
MESSAGE(STATUS "################################################\n")



# Include dirs
FIND_PATH(BRLCAD_INCLUDE_DIRS
  NAMES brlcad/bu.h
  PATHS ${INCLUDE_SEARCH_PATHS}
)

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
	tkimg   tkstub85  BLT24   
	itcl34   itclstub34   itk34   
	itkstub34
)
	FIND_LIBRARY( ${lib}_LIBRARY 
		NAMES ${lib}  
		PATHS ${LIB_SEARCH_PATHS}
	)
	SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} ${lib}_LIBRARY )
	IF(NOT ${lib}_LIBRARY)
		MESSAGE(STATUS "Could not find: ${lib}_LIBRARY ")
	ELSE(NOT ${lib}_LIBRARY)
		MESSAGE(STATUS "Found: ${lib}_LIBRARY \t${${lib}_LIBRARY}")
	ENDIF(NOT ${lib}_LIBRARY)


ENDFOREACH (lib)

return()










FIND_LIBRARY( bn_LIBRARY 
	NAMES bn  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} bn_LIBRARY )
IF(NOT bn_LIBRARY)
	MESSAGE(STATUS "Could not find: bn_LIBRARY")
ELSEIF(NOT bn_LIBRARY)
	MESSAGE(STATUS "Found: bn_LIBRARY")
ENDIF(NOT bn_LIBRARY)



FIND_LIBRARY( bu_LIBRARY 
	NAMES bu  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} bu_LIBRARY )
IF(NOT bu_LIBRARY)
	MESSAGE(STATUS "Could not find: bu_LIBRARY")
ENDIF(NOT bu_LIBRARY)



FIND_LIBRARY( dm_LIBRARY 
	NAMES dm  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} dm_LIBRARY )
IF(NOT dm_LIBRARY)
	MESSAGE(STATUS "Could not find: dm_LIBRARY")
ENDIF(NOT dm_LIBRARY)



FIND_LIBRARY( fb_LIBRARY 
	NAMES fb  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} fb_LIBRARY )
IF(NOT fb_LIBRARY)
	MESSAGE(STATUS "Could not find: fb_LIBRARY")
ENDIF(NOT fb_LIBRARY)



FIND_LIBRARY( ged_LIBRARY 
	NAMES ged  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} ged_LIBRARY )
IF(NOT ged_LIBRARY)
	MESSAGE(STATUS "Could not find: ged_LIBRARY")
ENDIF(NOT ged_LIBRARY)



FIND_LIBRARY( optical_LIBRARY 
	NAMES optical  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} optical_LIBRARY )
IF(NOT optical_LIBRARY)
	MESSAGE(STATUS "Could not find: optical_LIBRARY")
ENDIF(NOT optical_LIBRARY)



FIND_LIBRARY( orle_LIBRARY 
	NAMES orle  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} orle_LIBRARY )
IF(NOT orle_LIBRARY)
	MESSAGE(STATUS "Could not find: orle_LIBRARY")
ENDIF(NOT orle_LIBRARY)



FIND_LIBRARY( pkg_LIBRARY 
	NAMES pkg  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} pkg_LIBRARY )
IF(NOT pkg_LIBRARY)
	MESSAGE(STATUS "Could not find: pkg_LIBRARY")
ENDIF(NOT pkg_LIBRARY)



FIND_LIBRARY( png_LIBRARY 
	NAMES png  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} png_LIBRARY )
IF(NOT png_LIBRARY)
	MESSAGE(STATUS "Could not find: png_LIBRARY")
ENDIF(NOT png_LIBRARY)



FIND_LIBRARY( regex_LIBRARY 
	NAMES regex  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} regex_LIBRARY )
IF(NOT regex_LIBRARY)
	MESSAGE(STATUS "Could not find: regex_LIBRARY")
ENDIF(NOT regex_LIBRARY)



FIND_LIBRARY( rt_LIBRARY 
	NAMES rt  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} rt_LIBRARY )
IF(NOT rt_LIBRARY)
	MESSAGE(STATUS "Could not find: rt_LIBRARY")
ENDIF(NOT rt_LIBRARY)



FIND_LIBRARY( sysv_LIBRARY 
	NAMES sysv  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} sysv_LIBRARY )
IF(NOT sysv_LIBRARY)
	MESSAGE(STATUS "Could not find: sysv_LIBRARY")
ENDIF(NOT sysv_LIBRARY)



FIND_LIBRARY( tclcad_LIBRARY 
	NAMES tclcad  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} tclcad_LIBRARY )
IF(NOT tclcad_LIBRARY)
	MESSAGE(STATUS "Could not find: tclcad_LIBRARY")
ENDIF(NOT tclcad_LIBRARY)



FIND_LIBRARY( utahrle_LIBRARY 
	NAMES utahrle  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} utahrle_LIBRARY )
IF(NOT utahrle_LIBRARY)
	MESSAGE(STATUS "Could not find: utahrle_LIBRARY")
ENDIF(NOT utahrle_LIBRARY)



FIND_LIBRARY( wdb_LIBRARY 
	NAMES wdb  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} wdb_LIBRARY )
IF(NOT wdb_LIBRARY)
	MESSAGE(STATUS "Could not find: wdb_LIBRARY")
ENDIF(NOT wdb_LIBRARY)


FIND_LIBRARY( opennurbs_LIBRARY 
	NAMES opennurbs  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} opennurbs_LIBRARY )
IF(NOT opennurbs_LIBRARY)
	MESSAGE(STATUS "Could not find: opennurbs_LIBRARY")
ENDIF(NOT opennurbs_LIBRARY)


FIND_LIBRARY( tcl85_LIBRARY 
	NAMES tcl85  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} tcl85_LIBRARY )
IF(NOT tcl85_LIBRARY)
	MESSAGE(STATUS "Could not find: tcl85_LIBRARY")
ENDIF(NOT tcl85_LIBRARY)



FIND_LIBRARY( tclstub85_LIBRARY 
	NAMES tclstub85  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} tclstub85_LIBRARY )
IF(NOT tclstub85_LIBRARY)
	MESSAGE(STATUS "Could not find: tclstub85_LIBRARY")
ENDIF(NOT tclstub85_LIBRARY)



FIND_LIBRARY( tk85_LIBRARY 
	NAMES tk85  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} tk85_LIBRARY )
IF(NOT tk85_LIBRARY)
	MESSAGE(STATUS "Could not find: tk85_LIBRARY")
ENDIF(NOT tk85_LIBRARY)



FIND_LIBRARY( tkimg_LIBRARY 
	NAMES tkimg  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} tkimg_LIBRARY )
IF(NOT tkimg_LIBRARY)
	MESSAGE(STATUS "Could not find: tkimg_LIBRARY")
ENDIF(NOT tkimg_LIBRARY)



FIND_LIBRARY( tkstub85_LIBRARY 
	NAMES tkstub85 
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} tkstub85_LIBRARY )
IF(NOT tkstub85_LIBRARY)
	MESSAGE(STATUS "Could not find: tkstub85_library")
ENDIF(NOT tkstub85_LIBRARY)


FIND_LIBRARY( BLT24_LIBRARY 
	NAMES BLT24  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} BLT24_LIBRARY )
IF(NOT BLT24_LIBRARY)
	MESSAGE(STATUS "Could not find: BLT24_LIBRARY")
ENDIF(NOT BLT24_LIBRARY)



FIND_LIBRARY( itcl34_LIBRARY 
	NAMES itcl34  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} itcl34_LIBRARY )
IF(NOT itcl34_LIBRARY)
	MESSAGE(STATUS "Could not find: itcl34_LIBRARY")
ENDIF(NOT itcl34_LIBRARY)



FIND_LIBRARY( itclstub34_LIBRARY 
	NAMES itclstub34  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} itclstub34_LIBRARY )
IF(NOT itclstub34_LIBRARY)
	MESSAGE(STATUS "Could not find: itclstub34_LIBRARY")
ENDIF(NOT itclstub34_LIBRARY)



FIND_LIBRARY( itk34_LIBRARY 
	NAMES itk34  
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} itk34_LIBRARY )
IF(NOT itk34_LIBRARY)
	MESSAGE(STATUS "Could not find: itk34_LIBRARY")
ENDIF(NOT itk34_LIBRARY)



FIND_LIBRARY( itkstub34_LIBRARY 
	NAMES itkstub34 
	PATHS ${LIB_SEARCH_PATHS}
)
SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} itkstub34_LIBRARY )
IF(NOT itkstub34_LIBRARY)
	MESSAGE(STATUS "Could not find: itkstub34_library")
ENDIF(NOT itkstub34_LIBRARY)


