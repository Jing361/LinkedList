//
// Created by chris on 9/1/2019.
//

#ifndef GALACTICSTRUCTURES_SPLINE_HH
#define GALACTICSTRUCTURES_SPLINE_HH

#include <vector>
#include <polynomial.hh>
#include <initializer_list>

namespace gsw {

struct point2d{
  float x;
  float y;
};

/** Catmull-Rom
 * maybe take a polynomial as an argument?
 */
 //@todo: looping?
 /* floats are used because we don't care about the precision of a double, and floats will be faster/smaller
  */
class spline
{
private:
  gsw::polynomial mPoly0;
  gsw::polynomial mPoly1;
  gsw::polynomial mPoly2;
  gsw::polynomial mPoly3;

public:
  std::vector<point2d> points;/*!< manipulate the points directly */

  spline()
    : spline({})
  {}

  spline(std::initializer_list<point2d> il);

  point2d
  operator()(float p) const
  {
    return point(p);
  }

  point2d
  point(float p) const;

  point2d
  gradient(float p) const;

  float
  segmentLength(float p, float stepSize = 0.005f) const;
};

}

#endif //GALACTICSTRUCTURES_SPLINE_HH
