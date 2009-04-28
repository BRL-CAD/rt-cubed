// interface header
#include "Geometry/View.h"

using namespace Geometry;

View::View(double from[3], double at[3], double up[3], double angle, double hither)
{
  _from[0] = from[0];
  _from[1] = from[1];
  _from[2] = from[2];
  _at[0] = at[0];
  _at[1] = at[1];
  _at[2] = at[2];
  _up[0] = up[0];
  _up[1] = up[1];
  _up[2] = up[2];
  _angle = angle;
  _hither = hither;
}


View::~View()
{
  _from[0] = 0.0;
  _from[1] = 0.0;
  _from[2] = 0.0;
  _at[0] = 0.0;
  _at[1] = 0.0;
  _at[2] = 0.0;
  _up[0] = 0.0;
  _up[1] = 0.0;
  _up[2] = 0.0;
  _angle = 0.0;
  _hither = 0.0;
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8