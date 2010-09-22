CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

PROJECT(SUBVERSION)

SET(CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")

# build shared libs by default
OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)

# build static libs by default
OPTION(BUILD_STATIC_LIBS "Build static libraries" ON)

find_package(zlib)
find_package(sqlite3)
find_package(expat)

FIND_LIBRARY(APR_LIBRARY NAMES apr-1.0 PATHS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/../apr-install/lib NO_SYSTEM_PATH)
FIND_LIBRARY(APR_UTIL_LIBRARY NAMES aprutil-1.0 PATHS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/../apr-install/lib NO_SYSTEM_PATH)

include_directories(
	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include
	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include/private
	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/../apr-install/include/apr-1
	${ZLIB_INCLUDE_DIRS}
	#	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/apr/include/apr
	#  ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/apr/include/apr-util
)

ADD_SUBDIRECTORY(libsvn_subr)
ADD_SUBDIRECTORY(libsvn_delta)
ADD_SUBDIRECTORY(libsvn_fs_util)
ADD_SUBDIRECTORY(libsvn_fs_fs)
