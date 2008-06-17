project(g3d)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
include(${CMAKE_MODULE_PATH}/UsePkgConfig.cmake)

file(GLOB G3D_SOURCES *.cxx)
file(GLOB G3D_HEADERS *.h)
#source_group("Source Files" FILES ${SOURCES})
#source_group("Header Files" FILES ${HEADERS})

set(OGRE_CFG_FILES ../ogre.cfg  ../ogreplugins.cfg  ../resources.cfg)

add_definitions( -Wall -Wextra -g -DPOSIX )

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

  PKGCONFIG_WRAPPER("--cflags ${ESSENTIAL_LIBS}" PC_CFLAGS)
  PKGCONFIG_WRAPPER("--libs ${ESSENTIAL_LIBS}" PC_LDFLAGS)
  PKGCONFIG_WRAPPER("--variable=includedir ${ESSENTIAL_LIBS}" PC_INCLUDE_DIR)
  PKGCONFIG_WRAPPER("--variable=libdir ${ESSENTIAL_LIBS}" PC_LIB_DIR)

  include_directories(${PC_INCLUDE_DIR})
  link_directories(${PC_LIB_DIR})
  #link_libraries( g3d ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${Mocha_LIBRARIES} ${RBGui_LIBRARIES} )
  add_definitions(${PC_CFLAGS} ${PC_LDFLAGS})
  add_executable( g3d ${G3D_SOURCES} ${G3D_HEADERS} )
  target_link_libraries( g3d ${PC_LDFLAGS} )

  #install( TARGETS ${PROGNAME} DESTINATION bin )
  #install( FILES ${speedcrunch_TRANSLATIONS} DESTINATION share/crunch )
endif(CANNOT_BUILD)

