#
#   rt^3/src/GE/libRaytrace/CMakeLists.txt
#

set(LIBRAYTRACE_SOURCES
	init.cxx
)

ADD_LIBRARY (Raytrace SHARED ${LIBRAYTRACE_SOURCES})
