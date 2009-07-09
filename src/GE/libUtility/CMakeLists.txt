#
#   rt^3/src/GE/libUtility/CMakeLists.txt
#

set(LIBUTILITY_SOURCES
	init.cxx
	Application.cxx
	Date.cxx
	Time.cxx
	Timer.cxx
)

ADD_LIBRARY (Utility SHARED ${LIBUTILITY_SOURCES})
