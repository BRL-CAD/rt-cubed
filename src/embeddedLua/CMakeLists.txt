#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2017 United States Government as represented by
#	the U.S. Army Research Laboratory.
#
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public License
#	version 2.1 as published by the Free Software Foundation.
#
#	This library is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	Lesser General Public License for more details.
#
#	You should have received a copy of the GNU Lesser General Public
#	License along with this file; see the file named COPYING for more
#	information.
#
#########################################################################
#   @file rt^3/src/embeddedLua/CMakeLists.txt
#########################################################################

include_directories (
    ../other/lua/src
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (embeddedLua_SRC
    embeddedlua.cpp
    initbrlcad.cpp
    luadatabase.cpp
    writestring.cpp
    ../other/lua/src/lapi.c
    ../other/lua/src/lcode.c
    ../other/lua/src/lctype.c
    ../other/lua/src/ldebug.c
    ../other/lua/src/ldo.c
    ../other/lua/src/ldump.c
    ../other/lua/src/lfunc.c
    ../other/lua/src/lgc.c
    ../other/lua/src/llex.c
    ../other/lua/src/lmem.c
    ../other/lua/src/lobject.c
    ../other/lua/src/lopcodes.c
    ../other/lua/src/lparser.c
    ../other/lua/src/lstate.c
    ../other/lua/src/lstring.c
    ../other/lua/src/ltable.c
    ../other/lua/src/ltm.c
    ../other/lua/src/lundump.c
    ../other/lua/src/lvm.c
    ../other/lua/src/lzio.c
    ../other/lua/src/lauxlib.c
    ../other/lua/src/lbaselib.c
    ../other/lua/src/lbitlib.c
    ../other/lua/src/lcorolib.c
    ../other/lua/src/ldblib.c
    ../other/lua/src/liolib.c
    ../other/lua/src/lmathlib.c
    ../other/lua/src/loslib.c
    ../other/lua/src/lstrlib.c
    ../other/lua/src/ltablib.c
    ../other/lua/src/lutf8lib.c
    ../other/lua/src/loadlib.c
    ../other/lua/src/linit.c
)

add_definitions(-DLUA_USER_H=\\\"writestring.h\\\")
add_definitions(-Dlua_writestring=brlcad_writestring)
add_definitions(-Dlua_writeline=brlcad_writeline)
add_definitions(-Dlua_writestringerror=brlcad_writestringerror)

IF(MSVC)
    add_definitions("-DBRLCAD_COREINTERFACE_EXPORT=__declspec(dllimport)")
    add_definitions("-DBRLCAD_EMBEDDEDLUA_EXPORT=__declspec(dllexport)")
    add_definitions("-Dsnprintf=_snprintf")
ENDIF(MSVC)

IF(BUILD_SHARED_LIBS)
    add_library(embeddedlua SHARED ${embeddedLua_SRC})
    target_link_libraries(embeddedlua coreinterface)
    install(TARGETS embeddedlua DESTINATION lib)
ENDIF(BUILD_SHARED_LIBS)

IF(BUILD_STATIC_LIBS)
    add_library(embeddedlua-static STATIC ${embeddedLua_SRC})
    target_link_libraries(embeddedlua-static coreinterface-static)
    install(TARGETS embeddedlua-static DESTINATION lib)
ENDIF(BUILD_STATIC_LIBS)

SET(embeddedLua_HDRS
    ${RT3_SOURCE_DIR}/include/embeddedLua.h
)

INSTALL(FILES ${embeddedLua_HDRS} DESTINATION include)
