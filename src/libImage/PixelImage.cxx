// interface header
#include "Image/PixelImage.h"

using namespace Image;

PixelImage::PixelImage(unsigned long int width, unsigned long int height) :
  _width(width),
  _height(height)
{
}


PixelImage::~PixelImage()
{
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
