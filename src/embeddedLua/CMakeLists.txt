#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2017 United States Government as represented by
#	the U.S. Army Research Laboratory.
#
#	This file is in the public domain.
#
#	DISCLAIMER OF LIABILITY
#
#	THIS FILE WAS CAREFULLY TESTED BY THE AUTHOR AND IS MADE AVAILABLE TO YOU
#	FREE-OF-CHARGE IN A HIGH-GRADE ACTUAL STATUS. REFERENCE IS MADE HEREWITH TO
#	THE FACT THAT IT IS NOT POSSIBLE TO DEVELOP SOFTWARE PROGRAMS SO THAT THEY
#	ARE ERROR-FREE FOR ALL APPLICATION CONDITIONS. AS THE FILE IS LICENSED FREE
#	OF CHARGE THERE IS NO WARRANTY FOR IT, INSOFAR AS SUCH WARRANTY IS NOT A
#	MANDATORY REQUIREMENT OF THE APPLICABLE LAW, SUCH AS IN CASE OF WILFUL ACTS.
#	IN ADDITION THERE IS NO LIABILITY ALSO INSOFAR AS SUCH LIABILITY IS NOT A
#	MANDATORY REQUIREMENT OF THE APPLICABLE LAW, SUCH AS IN CASE OF WILFUL ACTS.
#
#	YOU DECLARE YOU ARE IN AGREEMENT WITH THE USE OF THIS FILE UNDER THE
#	ABOVE-LISTED USAGE CONDITIONS AND THE EXCLUSION OF A GUARANTEE AND OF
#	LIABILITY. SHOULD INDIVIDUAL PROVISIONS IN THESE CONDITIONS BE IN FULL OR IN
#	PART VOID, INVALID OR CONTESTABLE, THE VALIDITY OF ALL OTHER PROVISIONS OR
#	AGREEMENTS ARE UNAFFECTED BY THIS. FURTHER THE PARTIES UNDERTAKE AT THIS
#	JUNCTURE TO AGREE A LEGALLY VALID REPLACEMENT CLAUSE WHICH MOST CLOSELY
#	APPROXIMATES THE ECONOMIC OBJECTIVES.
#
#########################################################################
#   @file rt^3/src/embeddedLua/CMakeLists.txt
#########################################################################

include_directories (
    ../other/lua/src
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (embeddedLua_SRC
    ellipticaltorus.cpp
    embeddedlua.cpp
    halfspace.cpp
    hyperboliccylinder.cpp
    hyperboloid.cpp
    initbrlcad.cpp
    luadatabase.cpp
    sphere.cpp
    torus.cpp
    vector3d.cpp
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

add_definitions(-Dlua_writestring=brlcad_writestring)
add_definitions(-Dlua_writeline=brlcad_writeline)
add_definitions(-Dlua_writestringerror=brlcad_writestringerror)
add_definitions(-DLUA_USER_H="writestring.h")

IF(MSVC)
    add_definitions("-DBRLCAD_COREINTERFACE_EXPORT=__declspec(dllimport)")
    add_definitions("-DBRLCAD_EMBEDDEDLUA_EXPORT=__declspec(dllexport)")
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
    ${RT3_SOURCE_DIR}/include/embeddedlua.h
)

INSTALL(FILES ${embeddedLua_HDRS} DESTINATION include)
