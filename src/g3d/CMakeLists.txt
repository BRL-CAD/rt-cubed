project(g3d)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
include(${CMAKE_MODULE_PATH}/UsePkgConfig.cmake)

file(GLOB G3D_SOURCES *.cxx)
file(GLOB G3D_HEADERS *.h)
#source_group("Source Files" FILES ${SOURCES})
#source_group("Header Files" FILES ${HEADERS})

add_definitions( -Wall -Wextra -g -DPOSIX )

# Needed libraries
PKGCONFIG(OGRE 1.7.0 OGRE_INCLUDE_DIR OGRE_LINK_DIR OGRE_LINK_FLAGS OGRE_CFLAGS)
PKGCONFIG(OIS 1.2.0 OIS_INCLUDE_DIR OIS_LINK_DIR OIS_LINK_FLAGS OIS_CFLAGS)
PKGCONFIG(Mocha 0.1.3 Mocha_INCLUDE_DIR Mocha_LINK_DIR Mocha_LINK_FLAGS Mocha_CFLAGS)
PKGCONFIG(RBGui 0.1.3 RBGui_INCLUDE_DIR RBGui_LINK_DIR RBGui_LINK_FLAGS RBGui_CFLAGS)
set(ESSENTIAL_LIBS OGRE OIS Mocha RBGui)
foreach(l ${ESSENTIAL_LIBS})
  if(NOT ${l}_FOUND)
    message(SEND_ERROR "${l} library not found")
    set(CANNOT_BUILD true)
  endif(NOT ${l}_FOUND)
endforeach(l)

if(CANNOT_BUILD)
  message(FATAL_ERROR "Missing essential libraries, aborting")
else(CANNOT_BUILD)
  include_directories(${OGRE_INCLUDE_DIR} ${OIS_INCLUDE_DIR} ${Mocha_INCLUDE_DIR} ${RBGui_INCLUDE_DIR})
  add_definitions(${OGRE_CFLAGS} ${OIS_CFLAGS} ${Mocha_CFLAGS} ${RBGui_CFLAGS})
  add_executable( g3d ${G3D_SOURCES} ${G3D_HEADERS} )
  target_link_libraries( g3d ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${Mocha_LIBRARIES} ${RBGui_LIBRARIES} )

  #install( TARGETS ${PROGNAME} DESTINATION bin )
  #install( FILES ${speedcrunch_TRANSLATIONS} DESTINATION share/crunch )
endif(CANNOT_BUILD)

