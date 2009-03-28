# - Try to find libged
# Once done, this will define
#
#  libged_FOUND - system has libged
#  libged_INCLUDE_DIRS - the libged include directories
#  libged_LIBRARIES - link these to use libged

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(libged_PKGCONF libged)

# Include dir
find_path(libged_INCLUDE_DIR
  NAMES brlcad/ged.h
  PATHS ${libged_PKGCONF_INCLUDEDIR}
)

# Finally the library itself
find_library(libged_LIBRARY
  NAMES ged
  PATHS ${libged_PKGCONF_LIBDIR}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(libged_PROCESS_INCLUDES libged_INCLUDE_DIR)
set(libged_PROCESS_LIBS libged_LIBRARY)
libfind_process(libged)
