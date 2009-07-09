#
#   rt^3/src/GE/libGeometry/CMakeLists.txt
#

set(LIBGEOMETRY_SOURCES
	init.cxx 
	DXFFileParser.cxx 
	DXFFileParser.h 
	NFFFileParser.cxx 
	NFFFileParser.h 
	Point.cxx 
	Point.h 
	RGB.cxx 
	RGB.h 
	Scene.cxx 
	SceneFactory.cxx 
	Vec.cxx 
	Vec.h 
	View.cxx
)

ADD_LIBRARY (Geometry SHARED ${LIBGEOMETRY_SOURCES})
