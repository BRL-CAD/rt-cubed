#ifndef __PIXELIMAGE_H__
#define __PIXELIMAGE_H__

#include <string>

namespace Image 
{

  class PixelImage
  {
  protected:
    unsigned long int _width;
    unsigned long int _height;

    double _backgroundColor;
    
  public:
    PixelImage(unsigned long int width=1, unsigned long int height=1);
    ~PixelImage();

    inline unsigned long int getWidth() const;
    inline unsigned long int getHeight() const;

    void readFromFile(std::string filename);

  };

  inline unsigned long int PixelImage::getWidth() const
  {
    return _width;
  }

  inline unsigned long int PixelImage::getHeight() const
  {
    return _height;
  }

}



#endif  /* __PIXELIMAGE_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
