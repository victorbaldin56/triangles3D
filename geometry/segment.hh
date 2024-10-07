#ifndef TRIANGLES_3D_SEGMENT_HH_
#define TRIANGLES_3D_SEGMENT_HH_

#include <algorithm>

#include "line.hh"

namespace geometry {

template <typename T>
struct Segment {
  Point<T> a_, b_;

  Segment() : a_{}, b_{} {}
  Segment( const Point<T>& a, const Point<T>& b) : a_{a}, b_{b} {}

  Line<T> getLine() const {
    return Line<T>{a_ - b_, b_};
  }

  bool intersects( const Line<T>& line) const {
    Line<T> segment_line = getLine();
    auto point = getIntersection( segment_line, line);

    // check if intersection point is inside segment
    return containsLinePoint( point);
  }

  bool intersects( const Segment<T>& other) {
    Line<T> line = getLine();
    Line<T> other_line = other.getLine();
    auto point = getIntersection( line, other_line);

    return containsLinePoint( point) && other.containsLinePoint();
  }

 private:

  // FOR INTERNAL PURPOSE ONLY, assumes that a point is already on the segment's line
  bool containsLinePoint( const Point<T>& point) const {
    auto x_min = std::min( a_.x_, b_.x_), x_max = std::max( a_.x_, b_.x_);
    auto y_min = std::min( a_.y_, b_.y_), y_max = std::max( a_.y_, b_.y_);
    auto z_min = std::min( a_.z_, b_.z_), z_max = std::max( a_.z_, b_.z_);
    if ( x_min <= point.x_ && point.x_ <= x_max &&
         y_min <= point.y_ && point.y_ <= y_max &&
         z_min <= point.z_ && point.z_ <= z_max ) {
      return true;
    }

    return false;
  }
};

}

#endif // TRIANGLES_3D_SEGMENT_HH_
