# - Try to find libbu
# Once done, this will define
#
#  libbu_FOUND - system has libbu
#  libbu_INCLUDE_DIRS - the libbu include directories
#  libbu_LIBRARIES - link these to use libbu

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(libbu_PKGCONF libbu)

# Include dir
find_path(libbu_INCLUDE_DIR
  NAMES brlcad/bu.h
  PATHS ${libbu_PKGCONF_INCLUDEDIR}
)

# Finally the library itself
find_library(libbu_LIBRARY
  NAMES bu
  PATHS ${libbu_PKGCONF_LIBDIR}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(libbu_PROCESS_INCLUDES libbu_INCLUDE_DIR)
set(libbu_PROCESS_LIBS libbu_LIBRARY)
libfind_process(libbu)
