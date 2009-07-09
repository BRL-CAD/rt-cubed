#
#   rt^3/src/GE/libImage/CMakeLists.txt
#

set(LIBIMAGE_SOURCES
	init.cxx
	Pixel.cxx
	PixelImage.cxx
)

ADD_LIBRARY (Image SHARED ${LIBIMAGE_SOURCES})
