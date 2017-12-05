set (lua_SRC
    src/lapi.c
    src/lcode.c
    src/lctype.c
    src/ldebug.c
    src/ldo.c
    src/ldump.c
    src/lfunc.c
    src/lgc.c
    src/llex.c
    src/lmem.c
    src/lobject.c
    src/lopcodes.c
    src/lparser.c
    src/lstate.c
    src/lstring.c
    src/ltable.c
    src/ltm.c
    src/lundump.c
    src/lvm.c
    src/lzio.c
    src/lauxlib.c
    src/lbaselib.c
    src/lbitlib.c
    src/lcorolib.c
    src/ldblib.c
    src/liolib.c
    src/lmathlib.c
    src/loslib.c
    src/lstrlib.c
    src/ltablib.c
    src/lutf8lib.c
    src/loadlib.c
    src/linit.c
)

IF(BUILD_SHARED_LIBS)
    add_library(lua SHARED ${lua_SRC})
    install(TARGETS lua DESTINATION lib)
ENDIF(BUILD_SHARED_LIBS)

IF(BUILD_STATIC_LIBS)
    add_library(lua-static STATIC ${lua_SRC})
    install(TARGETS lua-static DESTINATION lib)
ENDIF(BUILD_STATIC_LIBS)

SET(lua_HDRS
    src/lua.h
    src/luaconf.h
    src/lualib.h
    src/lauxlib.h
    src/lua.hpp
)

INSTALL(FILES ${lua_HDRS} DESTINATION include)
