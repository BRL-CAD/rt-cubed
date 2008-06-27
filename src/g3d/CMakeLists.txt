project(g3d)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
include(${CMAKE_MODULE_PATH}/UsePkgConfig.cmake)

find_program(PKGCONFIG_EXECUTABLE NAMES pkg-config PATHS /usr/local/bin /usr/bin)
if(NOT PKGCONFIG_EXECUTABLE)
  message(FATAL_ERROR "Could not find 'pkg-config', necessary for configuration")
endif(NOT PKGCONFIG_EXECUTABLE)

#source_group("Source Files" FILES ${SOURCES})
#source_group("Header Files" FILES ${HEADERS})
set(PROGNAME "g3d")
file(GLOB G3D_SOURCES *.cxx)
file(GLOB G3D_HEADERS *.h)
set(RBGUI_DIR "../../data/g3d/RBGui")
add_definitions( -DDATA_DIR='"${CMAKE_INSTALL_PREFIX}/share/g3d/"' )

#include(CMakePrintSystemInformation)
#include(FindPkgConfig)

# basic compiler flags
add_definitions( -Wall -Wextra -g )

# detect OS
set(SYSTEM "POSIX")
if(WIN32)
  set(SYSTEM "WIN32")
endif(WIN32)
if(APPLE)
  set(SYSTEM "APPLE")
endif(APPLE)
add_definitions( -D${SYSTEM} )
message(STATUS "Detected system name '${CMAKE_SYSTEM_NAME}', building for system '${SYSTEM}'")

# Needed libraries
set(ESSENTIAL_LIBS OGRE OIS Mocha RBGui)
PKGCONFIG_ATLEAST(OGRE 1.7.0 OGRE_FOUND)
PKGCONFIG_ATLEAST(OIS 1.2.0 OIS_FOUND)
PKGCONFIG_ATLEAST(Mocha 0.1.3 Mocha_FOUND)
PKGCONFIG_ATLEAST(RBGui 0.1.3 RBGui_FOUND)
foreach(l ${ESSENTIAL_LIBS})
  if(NOT ${l}_FOUND)
    message(SEND_ERROR "${l} library not found")
    set(CANNOT_BUILD true)
  endif(NOT ${l}_FOUND)
endforeach(l)

if(CANNOT_BUILD)
  message(FATAL_ERROR "Missing essential libraries, aborting")
else(CANNOT_BUILD)
  PKGCONFIG_WRAPPER("--cflags ${ESSENTIAL_LIBS}" PC_CFLAGS PC_EXIT_CODE)
  PKGCONFIG_WRAPPER("--libs ${ESSENTIAL_LIBS}" PC_LDFLAGS PC_EXIT_CODE)
  PKGCONFIG_WRAPPER("--variable=includedir ${ESSENTIAL_LIBS}" PC_INCLUDE_DIR PC_EXIT_CODE)
  PKGCONFIG_WRAPPER("--variable=libdir ${ESSENTIAL_LIBS}" PC_LIB_DIR PC_EXIT_CODE)

  include_directories(${PC_INCLUDE_DIR})
  link_directories(${PC_LIB_DIR})
  #link_libraries( g3d ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${Mocha_LIBRARIES} ${RBGui_LIBRARIES} )
  add_definitions(${PC_CFLAGS})
  add_executable( g3d ${G3D_SOURCES} ${G3D_HEADERS} )
  target_link_libraries( g3d ${PC_LDFLAGS} )

  # OGRE config files
  file(WRITE ${PROJECT_BINARY_DIR}/resources.cfg "# Resource locations to be added to the default path
[General]
FileSystem=${CMAKE_INSTALL_PREFIX}/share/g3d/RBGui/materials/programs
FileSystem=${CMAKE_INSTALL_PREFIX}/share/g3d/RBGui/materials/scripts
FileSystem=${CMAKE_INSTALL_PREFIX}/share/g3d/RBGui/fonts
FileSystem=${CMAKE_INSTALL_PREFIX}/share/g3d/RBGui/themes")
  PKGCONFIG_WRAPPER("--variable=plugindir OGRE" PC_OGREPLUGIN_DIR PC_EXIT_CODE)
  file(WRITE ${PROJECT_BINARY_DIR}/ogreplugins.cfg "# Defines plugins to load
PluginFolder=${PC_OGREPLUGIN_DIR}
Plugin=RenderSystem_GL
Plugin=Plugin_OctreeSceneManager")
  file(GLOB OGRE_CFG_FILES ${PROJECT_BINARY_DIR}/*.cfg)

  install( TARGETS ${PROGNAME} DESTINATION bin )
  install( FILES ${RBGUI_FILES} ${OGRE_CFG_FILES} DESTINATION share/g3d )
  install( DIRECTORY ${RBGUI_DIR} DESTINATION share/g3d PATTERN ".svn" EXCLUDE)
endif(CANNOT_BUILD)
