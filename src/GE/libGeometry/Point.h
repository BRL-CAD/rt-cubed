#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "Vec.h"

using std::cout;
using std::endl;


/**
 *  Stores a point consisting of x,y, and z components; has methods to get x,y,z values,
 *  to set x,y,z values and to add or subtract two points componentwise.
 */
class Point {
 public:
  /** Creates a point at (0,0,0) */
  Point();
  /** Creates a point at (x,y,z) */
  Point(double x, double y, double z);

  inline double getZ() {
    return Z;
  }


  inline double getY() {
    return Y;
  }


  inline double getX() {
    return X;
  }



#if 0
  /** gets x value */
  double getX();
  /** gets y value */
  double getY();
  /** gets z value */
  double getZ();
#endif
  /** sets x,y,z values */
  void setPt(double x, double y, double z);
  /** adds two points to return a vector */
  Vec add(Point &p, Point &q);
  /** subtracts two points to return a vector */
  Vec sub(Point &p, Point &q);
  /** does a brl-cad style join1 */
  Point join1(Point &pt, double dist, Vec &dir);

  friend std::ostream&
    operator<<(std::ostream&, const Point&);

  /** the point consisting of three components */
  //    double p[3];
  double X;
  double Y;
  double Z;
};
#else
class Point;
#endif //POINT_H