#ifndef TRIANGLES_3D_LINE_HH_
#define TRIANGLES_3D_LINE_HH_

#include "point.hh"

namespace geometry {

template <typename T>
class Line {
  Point<T> direction_, origin_;

 public:
  Line() {}
  Line( const Point<T>& direction, const Point<T>& origin)
    : direction_{Point<T>{direction}.normalize()}, origin_{origin} {}

  bool valid() const {
    return direction_.valid() && origin_.valid();
  }

  const Point<T>& origin() const {
    return origin_;
  }

  const Point<T>& direction() const {
    return direction_;
  }

  bool coincidentWith( const Line<T>& rhs) const {
    return collinear( direction_, rhs.direction_) &&
           collinear( origin_ - rhs.origin_, direction_);
  }

  Point<T> getIntersection( const Line<T>& rhs) const {
    if ( coincidentWith( rhs) ) {
      return Point<T>{};
    }

    auto diff = rhs.origin_ - origin_;

    // skew case
    if ( !coplanar( diff, direction_, rhs.direction_) ) {
      return Point<T>{};
    }

    auto cross = crossProduct( direction_, rhs.direction_);

    return origin_ +
           direction_ * ((scalarProduct( crossProduct( diff, rhs.direction_), cross)) /
           cross.length2());
  }
};

template <typename T>
inline bool coincident( const Line<T>& a, const Line<T>& b) {
  return a.coincidentWith( b);
}

template <typename T>
inline Point<T> getIntersection( const Line<T>& a, const Line<T>& b) {
  return a.getIntersection( b);
}

}

#endif // TRIANGLES_3D_LINE_HH_
