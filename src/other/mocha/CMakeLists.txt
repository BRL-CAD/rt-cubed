cmake_minimum_required(VERSION 2.2)
project(mocha)

# basic compiler flags
add_definitions()

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

# compilation
file(GLOB MOCHA_SOURCES Source/*.cpp Lua/*.c)
include_directories(Include/ Lua/)
add_library(mocha SHARED ${MOCHA_SOURCES})
set_target_properties(mocha PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(mocha pthread uuid)

# pkg-config file
file(WRITE ${PROJECT_BINARY_DIR}/Mocha.pc "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/lib
includedir=\${prefix}/include

Name: Mocha
Description: Helper library for RBGui
Version: 0.1.3
Libs: -L\${libdir} -lmocha
Cflags: -I\${includedir} -I\${includedir}/Mocha")
set(PKGCONFIG_FILES ${PROJECT_BINARY_DIR}/Mocha.pc)

# installation
install(TARGETS mocha LIBRARY DESTINATION lib)
install(DIRECTORY Include/ DESTINATION include PATTERN ".svn" EXCLUDE)
install(FILES ${PKGCONFIG_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/)
