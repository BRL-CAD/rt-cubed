#
#   rt^3/src/GE/libNumeric/CMakeLists.txt
#

set(LIBNUMERIC_SOURCES
	init.cxx
)

ADD_LIBRARY (Numeric SHARED ${LIBNUMERIC_SOURCES})
