#include "Point.h"

std::ostream&
operator<<(std::ostream& s, const Point& p)
{
    return s << p.X << " " << p.Y << " " << p.Z << " ";
}

Point::Point() {
  X = Y = Z = 0.0;
}


Point::Point(double x, double y, double z) {
	X = x;
  Y = y;
  Z = z;
}


Vec Point::sub(Point &p, Point &q) {
  Vec	V;

  V.setVec(p.X - q.X, p.Y - q.Y, p.Z - q.Z);
  return V;
}


Vec Point::add(Point &p, Point &q) {
  Vec	V;

  V.setVec(p.X + q.X, p.Y + q.Y, p.Z + q.Z);
  return V;
}


void Point::setPt(double x, double y, double z) {
  X = x;
  Y = y;
  Z = z;
}




Point Point::join1(Point &pt, double dist, Vec &dir) {
  Point		T;

  T.setPt(pt.X + dist*dir.X, pt.Y + dist*dir.Y, pt.Z + dist*dir.Z);
  return(T);
}
