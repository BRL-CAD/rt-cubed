#ifndef __RAY_H__
#define __RAY_H__

#include <iostream>

#include "Ray.h"

namespace Geometry {

  class Ray
  {
  private:
    double _position[3];
    double _direction[3];
    
  public:
    Ray(double position[3], double direction[3]);
    ~Ray();
  };


  Ray::Ray(double position[3], double direction[3])
  {
    _position[0] = position[0];
    _position[1] = position[1];
    _position[2] = position[2];

    _direction[0] = direction[0];
    _direction[1] = direction[0];
    _direction[0] = direction[0];
  }

}


#endif  /* __RAY_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
