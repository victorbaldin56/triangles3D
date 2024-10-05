#ifndef TRIANGLES_3D_SEGMENT_HH_
#define TRIANGLES_3D_SEGMENT_HH_

#include "line.hh"

namespace geometry {

template <typename T>
struct Segment {
  Point<T> a_, b_;

  Segment() : a_{}, b_{} {}
  Segment( const Point<T>& a, const Point<T>& b) : a_{a}, b_{b} {}

  bool intersects( const Line<T>& line) const {

  }
};

}

#endif // TRIANGLES_3D_SEGMENT_HH_
