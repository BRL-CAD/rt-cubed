cmake_minimum_required(VERSION 2.2)
project(g3d)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../../cmake/")
include(${CMAKE_MODULE_PATH}/UsePkgConfig.cmake)
include(${CMAKE_MODULE_PATH}/UseBrlcadConfig.cmake)

set(PROGNAME "g3d")
set(G3D_SOURCES
  CameraMode.cxx
  CameraModeBlender.cxx
  CameraModeMGED.cxx
  CameraModeOrbital.cxx
  Command.cxx
  CommandInterpreter.cxx
  GedCommand.cxx
  GedData.cxx
  Console.cxx
  OgreGLWidget.cxx
  History.cxx
  Logger.cxx
  Observer.cxx
  MainWindow.cxx
  main.cxx
  )

set(G3D_HEADERS
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
  Console.h
  History.h
  Logger.h
  Observer.h
  MainWindow.h
  )

# Qt stuff that needs preprocessing
set(G3D_MOC_HEADERS
  OgreGLWidget.h
  MainWindow.h
  Console.h
  )

set(G3D_UIS
  mainwindow.ui
  )

set(RBGUI_DIR "../../data/g3d/RBGui")
add_definitions( -DDATA_DIR='"${CMAKE_INSTALL_PREFIX}/share/g3d/"' )

# basic compiler flags
add_definitions( -Wall -Wextra )

# Needed libraries
find_package(OGRE REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OGRE_LIBRARIES})

find_package(libged REQUIRED)
include_directories(${libged_INCLUDE_DIRS})
set(LIBS ${LIBS} ${libged_LIBRARIES})

find_package(libbu REQUIRED)
include_directories(${libbu_INCLUDE_DIRS})
set(LIBS ${LIBS} ${libbu_LIBRARIES})

find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})
set(LIBS ${LIBS} ${QT_LIBRARIES})

# Preprocess Qt stuff
qt4_wrap_cpp(G3D_MOC_OUTFILES ${G3D_MOC_HEADERS})
qt4_wrap_ui(G3D_UI_OUTFILES ${G3D_UIS})

add_executable( g3d ${G3D_SOURCES} ${G3D_MOC_OUTFILES} ${G3D_HEADERS} ${G3D_UI_OUTFILES})
target_link_libraries( g3d ${LIBS} )

# OGRE config files
file(WRITE ${PROJECT_BINARY_DIR}/resources.cfg "# Resource locations to be added to the default path
[General]
FileSystem=${CMAKE_INSTALL_PREFIX}/share/g3d/")
file(WRITE ${PROJECT_BINARY_DIR}/ogreplugins.cfg "# Defines plugins to load
PluginFolder=${OGRE_PLUGIN_DIR_REL}
Plugin=RenderSystem_GL
Plugin=Plugin_OctreeSceneManager")

set(OGRE_CFG_FILES ${PROJECT_BINARY_DIR}/resources.cfg ${PROJECT_BINARY_DIR}/ogreplugins.cfg ${PROJECT_BINARY_DIR}/ogre.cfg)

install( TARGETS ${PROGNAME} DESTINATION bin )
install( FILES ${OGRE_CFG_FILES} DESTINATION share/g3d )
install( FILES knot.mesh DESTINATION share/g3d )
install( DIRECTORY DESTINATION share/g3d PATTERN ".svn" EXCLUDE)
