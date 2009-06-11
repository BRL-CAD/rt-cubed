# - Try to find RBGui
# Once done, this will define
#
#  RBGui_FOUND - system has RBGui
#  RBGui_INCLUDE_DIRS - the RBGui include directories
#  RBGui_LIBRARIES - link these to use RBGui

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(RBGui_PKGCONF RBGui)

# Include dir
find_path(RBGui_INCLUDE_DIR
  NAMES RBGui/Core.h
  PATHS ${RBGui_PKGCONF_INCLUDEDIR}
)

# Finally the library itself
find_library(RBGui_LIBRARY
  NAMES rbgui
  PATHS ${RBGui_PKGCONF_LIBDIR}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(RBGui_PROCESS_INCLUDES RBGui_INCLUDE_DIR)
set(RBGui_PROCESS_LIBS RBGui_LIBRARY)
libfind_process(RBGui)
