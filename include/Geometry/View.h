#ifndef __VIEW_H__
#define __VIEW_H__

#include <iostream>
#include <vector>

#include "Geometry/Triangle.h"
#include "Geometry/View.h"


namespace Geometry {

  class View
  {
  private:
    double _from[3];
    double _at[3];
    double _up[3];
    double _angle;
    double _hither;
    
    double _x;
    double _y;
  protected:
  public:
    View(double from[3], double at[3], double up[3], double angle, double hither);
    ~View();

    void setResolution(unsigned long int x, unsigned long int y) {
      _x = x;
      _y = y;
    }

  };

}

#endif  /* __VIEW_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
