CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

PROJECT(SUBVERSION)

SET(CMAKE_MODULE_PATH "${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")

INCLUDE(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/CMake/SVN_CheckFunctions.cmake)

SET(SVN_CONFIG_H_FILE "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include/svn_private_config.h.in")
FILE(WRITE ${SVN_CONFIG_H_FILE} "/**** Define statements for Subversion ****/\n")

# Define some basic info
SET(PACKAGE_NAME "subversion")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine PACKAGE_NAME \"${PACKAGE_NAME}\"\n")
SET(PACKAGE_VERSION "1.6.12")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine PACKAGE_VERSION \"${PACKAGE_VERSION}\"\n")
SET(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine PACKAGE_STRING \"${PACKAGE_STRING}\"\n")
SET(PACKAGE_TARNAME "${PACKAGE_NAME}")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine PACKAGE_TARNAME \"${PACKAGE_TARNAME}\"\n")

SET(PACKAGE_URL "http://brlcad.org")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine PACKAGE_URL \"${PACKAGE_URL}\"\n")
SET(PACKAGE_BUGREPORT "http://brlcad.org")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine PACKAGE_BUGREPORT \"${PACKAGE_BUGREPORT}\"\n")


# Since this is used only on Unix-y systems, define the path separator as '/'
SET(SVN_PATH_LOCAL_SEPARATOR "/")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine SVN_PATH_LOCAL_SEPARATOR '${SVN_PATH_LOCAL_SEPARATOR}'\n")

# Null device for the system
SET(SVN_NULL_DEVICE_NAME "/dev/null")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine SVN_NULL_DEVICE_NAME \"${SVN_NULL_DEVICE_NAME}\"\n")

# Build FSFS by default
SET(DEFAULT_FS_TYPE "fsfs")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine DEFAULT_FS_TYPE \"${DEFAULT_FS_TYPE}\"\n")

# Installed binary dir
SET(SVN_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine SVN_BINDIR \"${SVN_BINDIR}\"\n")

# Expand locale dir
SET(SVN_LOCALE_DIR "${CMAKE_INSTALL_PREFIX}/share")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#cmakedefine SVN_LOCALE_DIR \"${SVN_LOCALE_DIR}\"\n")


FILE(APPEND ${SVN_CONFIG_H_FILE} "#define SVN_LIBSVN_CLIENT_LINKS_RA_LOCAL 1")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#define SVN_LIBSVN_CLIENT_LINKS_RA_SVN 1")
FILE(APPEND ${SVN_CONFIG_H_FILE} "#define SVN_LIBSVN_CLIENT_LINKS_FS_FS 1")

SVN_INCLUDE_FILE(dlfcn.h HAVE_DLFCN_H)
SVN_INCLUDE_FILE(inttypes.h HAVE_INTTYPES_H)
SVN_CHECK_LIBRARY(ICONV iconv libiconv_open)
SVN_CHECK_LIBRARY(SOCKET socket socket)
SVN_INCLUDE_FILE(memory.h HAVE_MEMORY_H)
SVN_FUNCTION_EXISTS(rb_errinfo HAVE_RB_ERRINFO)
SVN_FUNCTION_EXISTS(readlink HAVE_READLINK)
SVN_INCLUDE_FILE(serf.h HAVE_SERF_H)
SVN_INCLUDE_FILE(stdint.h HAVE_STDINT_H)
SVN_INCLUDE_FILE(stdlib.h HAVE_STDLIB_H)
SVN_INCLUDE_FILE(strings.h HAVE_STRINGS_H)
SVN_INCLUDE_FILE(string.h HAVE_STRING_H)
SVN_FUNCTION_EXISTS(symlink HAVE_SYMLINK)
SVN_INCLUDE_FILE(sys/stat.h HAVE_SYS_STAT_H)
SVN_INCLUDE_FILE(sys/types.h HAVE_SYS_TYPES_H)
SVN_INCLUDE_FILE(unistd.h HAVE_UNISTD_H)
SVN_FUNCTION_EXISTS(vprintf HAVE_VPRINTF)
SVN_INCLUDE_FILE(zlib.h HAVE_ZLIB_H)


# build shared libs by default
OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)

# build static libs by default
OPTION(BUILD_STATIC_LIBS "Build static libraries" ON)

find_package(zlib)
find_package(expat)

FIND_LIBRARY(APR_LIBRARY NAMES apr-1.0 PATHS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/../apr-install/lib NO_SYSTEM_PATH)
FIND_LIBRARY(APR_UTIL_LIBRARY NAMES aprutil-1.0 PATHS ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/../apr-install/lib NO_SYSTEM_PATH)

find_package(sqlite3)
IF(NOT SQLITE3_LIBRARIES)
	FILE(APPEND ${SVN_CONFIG_H_FILE} "#define SVN_SQLITE_INLINE 1")
ENDIF(NOT SQLITE3_LIBRARIES)

SET(SVN_CONF_H_ENDING "
#define N_(x) x
#define U_(x) x
#ifdef ENABLE_NLS
#include <locale.h>
#include <libintl.h>
#define _(x) dgettext(PACKAGE_NAME, x)
#define Q_(x1, x2, n) dngettext(PACKAGE_NAME, x1, x2, n)
#else
#define _(x) (x)
#define Q_(x1, x2, n) (((n) == 1) ? x1 : x2)
#define gettext(x) (x)
#define dgettext(domain, x) (x)
#endif
")

FILE(APPEND ${SVN_CONFIG_H_FILE} "${SVN_CONF_H_ENDING}")

include_directories(
	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include
	${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include
	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include/private
	${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/../apr-install/include/apr-1
	${ZLIB_INCLUDE_DIRS}
)

# Now that all the tests are done, configure the svn_private_config.h file:
configure_file(${SVN_CONFIG_H_FILE} ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/include/svn_private_config.h)

ADD_SUBDIRECTORY(libsvn_subr)
ADD_SUBDIRECTORY(libsvn_delta)
ADD_SUBDIRECTORY(libsvn_fs_util)
ADD_SUBDIRECTORY(libsvn_fs_fs)
