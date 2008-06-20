# Find Mocha includes and library
#
# This module defines
#  Mocha_INCLUDE_DIR
#  Mocha_LIBRARIES, the libraries to link against to use Mocha.
#  Mocha_FOUND, If false, do not try to use OGRE
#
# Copyright Â© 2007, Matt Williams
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (Mocha_LIBRARIES AND Mocha_INCLUDE_DIR)
	SET(Mocha_FIND_QUIETLY TRUE) # Already in cache, be silent
ENDIF (Mocha_LIBRARIES AND Mocha_INCLUDE_DIR)

FIND_LIBRARY(Mocha_LIBRARIES mocha /lib /usr/lib /usr/local/lib)
FIND_PATH(Mocha_INCLUDE_DIR WeakRefPointer.h /usr/include/Mocha /usr/local/include/Mocha)

#Do some preparation
SEPARATE_ARGUMENTS(Mocha_INCLUDE_DIR)
SEPARATE_ARGUMENTS(Mocha_LIBRARIES)

SET(Mocha_INCLUDE_DIR ${Mocha_INCLUDE_DIR} CACHE PATH "")
SET(Mocha_LIBRARIES ${Mocha_LIBRARIES} CACHE STRING "")

IF (Mocha_INCLUDE_DIR AND Mocha_LIBRARIES)
	SET(Mocha_FOUND TRUE)
ENDIF (Mocha_INCLUDE_DIR AND Mocha_LIBRARIES)

IF (Mocha_FOUND)
	IF (NOT Mocha_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${Mocha_LIBRARIES}")
		MESSAGE(STATUS "  includes  : ${Mocha_INCLUDE_DIR}")
	ENDIF (NOT Mocha_FIND_QUIETLY)
ELSE (Mocha_FOUND)
	IF (Mocha_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find Mocha")
	ENDIF (Mocha_FIND_REQUIRED)
ENDIF (Mocha_FOUND)
