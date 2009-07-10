cmake_minimum_required(VERSION 2.2)
project(g3d)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../../cmake/")
include(${CMAKE_MODULE_PATH}/UsePkgConfig.cmake)
include(${CMAKE_MODULE_PATH}/UseBrlcadConfig.cmake)

find_program(PKGCONFIG_EXECUTABLE NAMES pkg-config PATHS /usr/local/bin /usr/bin)
if(NOT PKGCONFIG_EXECUTABLE)
  message(FATAL_ERROR "Could not find 'pkg-config', necessary for configuration")
endif(NOT PKGCONFIG_EXECUTABLE)

#source_group("Source Files" FILES ${SOURCES})
#source_group("Header Files" FILES ${HEADERS})
set(PROGNAME "g3d")
set(G3D_SOURCES
  Application.cxx
  CameraManager.cxx
  CameraMode.cxx
  CameraModeBlender.cxx
  CameraModeMGED.cxx
  CameraModeOrbital.cxx
  Command.cxx
  CommandInterpreter.cxx
  GedCommand.cxx
  GedData.cxx
  GeometryConversion.cxx
  GuiBaseWindow.cxx
  GuiCamera.cxx
  GuiCommandOverlay.cxx
  GuiConsole.cxx
  GuiWidgetRotation.cxx
  GuiWindowManager.cxx
  History.cxx
  Logger.cxx
  Observer.cxx
  OgreScene.cxx
  main.cxx
  )

set(OGRETEST_SOURCES
  ogretest.cxx
  Logger.cxx
  Observer.cxx
  OgreScene.cxx
  )

set(G3D_HEADERS
  Application.h
  CameraManager.h
  CameraMode.h
  CameraModeBlender.h
  CameraModeMGED.h
  CameraModeOrbital.h
  Command.h
  Commands.h
  CommandInterpreter.h
  GedCommand.h
  GedCommands.h
  GedData.h
  GeometryConversion.h
  GuiBaseWindow.h
  GuiCamera.h
  GuiCommandOverlay.h
  GuiConsole.h
  GuiWidgetRotation.h
  GuiWindowManager.h
  History.h
  Logger.h
  Observer.h
  )

# Qt stuff that needs preprocessing
set(G3D_MOC_HEADERS
  OgreScene.h
  )

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
message(STATUS "Will use C++ compiler '${CMAKE_CXX_COMPILER}'")

# Needed libraries
find_package(OGRE REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OGRE_LIBRARIES})
set(OTLIBS ${OTLIBS} ${OGRE_LIBRARIES})

find_package(OIS REQUIRED)
include_directories(${OIS_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OIS_LIBRARIES})

find_package(libged REQUIRED)
include_directories(${libged_INCLUDE_DIRS})
set(LIBS ${LIBS} ${libged_LIBRARIES})

find_package(libbu REQUIRED)
include_directories(${libbu_INCLUDE_DIRS})
set(LIBS ${LIBS} ${libbu_LIBRARIES})

find_package(Mocha REQUIRED)
include_directories(${Mocha_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Mocha_LIBRARIES})

find_package(RBGui REQUIRED)
include_directories(${RBGui_INCLUDE_DIRS})
set(LIBS ${LIBS} ${RBGui_LIBRARIES})

find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})
#set(LIBS ${LIBS} ${QT_LIBRARIES})
set(OTLIBS ${OTLIBS} ${QT_LIBRARIES})

# Preprocess Qt stuff
qt4_wrap_cpp(G3D_MOC_OUTFILES ${G3D_MOC_HEADERS})

if(CANNOT_BUILD)
  message(FATAL_ERROR "Missing essential libraries, aborting")
else(CANNOT_BUILD)
  #PKGCONFIG_WRAPPER("--cflags ${ESSENTIAL_LIBS}" PC_CFLAGS PC_EXIT_CODE)
  #PKGCONFIG_WRAPPER("--libs ${ESSENTIAL_LIBS}" PC_LDFLAGS PC_EXIT_CODE)
  #PKGCONFIG_WRAPPER("--variable=includedir ${ESSENTIAL_LIBS}" PC_INCLUDE_DIR PC_EXIT_CODE)
  #PKGCONFIG_WRAPPER("--variable=libdir ${ESSENTIAL_LIBS}" PC_LIB_DIR PC_EXIT_CODE)

  #BRLCADCONFIG_WRAPPER("--cflags" BRLCAD_CFLAGS BRLCAD_EXIT_CODE)
  #BRLCADCONFIG_WRAPPER("--libs ged" BRLCAD_LDFLAGS BRLCAD_EXIT_CODE)
  #BRLCADCONFIG_WRAPPER("--includedir" BRLCAD_INCLUDE_DIR BRLCAD_EXIT_CODE)
  #BRLCADCONFIG_WRAPPER("--libdir" BRLCAD_LIB_DIR BRLCAD_EXIT_CODE)

  #link_directories(${PC_LIB_DIR} ${BRLCAD_LIB_DIR})

  # Not necessary at the moment, maybe never
  #if(TCL_INCLUDE)
  #  include_directories(${TCL_INCLUDE})
  #endif(TCL_INCLUDE)
  #if(TCL_LIB)
  #  link_directories(${TCL_LIB})
  #endif(TCL_LIB)

  #link_libraries( g3d ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${Mocha_LIBRARIES} ${RBGui_LIBRARIES} )
  #add_definitions(${PC_CFLAGS} ${BRLCAD_CFLAGS})
  add_executable( g3d ${G3D_SOURCES} ${G3D_MOC_OUTFILES} ${G3D_HEADERS} )
  add_executable( ogretest ${OGRETEST_SOURCES} ${G3D_MOC_OUTFILES} ${G3D_HEADERS} )
  target_link_libraries( g3d ${LIBS} )
  target_link_libraries( ogretest ${OTLIBS} )

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
  set(OGRE_CFG_FILES ${PROJECT_BINARY_DIR}/resources.cfg ${PROJECT_BINARY_DIR}/ogreplugins.cfg)

  install( TARGETS ${PROGNAME} DESTINATION bin )
  install( FILES ${RBGUI_FILES} ${OGRE_CFG_FILES} DESTINATION share/g3d )
  install( DIRECTORY ${RBGUI_DIR} DESTINATION share/g3d PATTERN ".svn" EXCLUDE)
endif(CANNOT_BUILD)
