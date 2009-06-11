# - Try to find Mocha
# Once done, this will define
#
#  Mocha_FOUND - system has Mocha
#  Mocha_INCLUDE_DIRS - the Mocha include directories
#  Mocha_LIBRARIES - link these to use Mocha

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Mocha_PKGCONF Mocha)

# Include dir
find_path(Mocha_INCLUDE_DIR
  NAMES Mocha/AABB.h
  PATHS ${Mocha_PKGCONF_INCLUDEDIR}
)

# Finally the library itself
find_library(Mocha_LIBRARY
  NAMES mocha
  PATHS ${Mocha_PKGCONF_LIBDIR}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Mocha_PROCESS_INCLUDES Mocha_INCLUDE_DIR)
set(Mocha_PROCESS_LIBS Mocha_LIBRARY)
libfind_process(Mocha)
