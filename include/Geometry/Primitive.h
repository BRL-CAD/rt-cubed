#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <iostream>

namespace Geometry {

  class Primitive
  {
  private:
  protected:
    /*    Primitive() {};
    virtual ~Primitive() = 0;
    */
  public:
    virtual bool intersect(double position[3], double direction[3], double *t, double *u, double *v) = 0;
  };

}

#endif  /* __PRIMITIVE_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
