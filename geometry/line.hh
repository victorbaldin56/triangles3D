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

  bool isValid() const {
    return direction_.isValid() && origin_.isValid();
  }

  bool coincident( const Line<T>& rhs) const {
    return collinear( direction_, rhs.direction_) &&
           collinear( origin_ - rhs.origin_, direction_);
  }

  Point<T> getIntersection( const Line<T>& rhs) const {
    if ( coincident( rhs) ) {
      return Point<T>{};
    }

    auto diff = rhs.origin_ - origin_;

    // skew case
    if ( !coplanar( diff, direction_, rhs.direction_) ) {
      return Point<T>{};
    }

    auto cross = crossProduct( direction_, rhs.direction_);

    return origin_ +
          (direction_ * (scalarProduct( crossProduct( diff, rhs.direction_),
                                         crossProduct( origin_, diff)))
          / scalarProduct( cross, cross));

  }
};

template <typename T>
inline bool coincident( const Line<T>& a, const Line<T>& b) {
  return a.coincident( b);
}

template <typename T>
inline Point<T> getIntersection( const Line<T>& a, const Line<T>& b) {
  return a.getIntersection( b);
}

}

#endif // TRIANGLES_3D_LINE_HH_
