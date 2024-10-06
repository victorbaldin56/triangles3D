#ifndef TRIANGLES_3D_LINE_HH_
#define TRIANGLES_3D_LINE_HH_

#include "point.hh"

namespace geometry {

template <typename T>
struct Line {
  Point<T> direction_, origin_;

  Line() {}
  Line( const Point<T>& a, const Point<T>& b) : direction_{(a - b).normalize()}, origin_{a} {}

  bool is_valid() const {
    return direction_.is_valid() && origin_.is_valid();
  }
};

template <typename T>
inline bool coincident( const Line<T>& a, const Line<T>& b) {
  return is_close( a.direction_, b.direction_) && collinear( a.origin_ - b.origin_, a.direction_);
}

template <typename T>
inline Point<T> get_intersection( const Line<T>& a, const Line<T>& b) {
  if ( coincident( a, b) ) {
    return Point<T>{};
  }

  auto diff = b.origin_ - a.origin_;

  // skew case
  if ( !coplanar( diff, a.direction_, b.direction_) ) {
    return Point<T>{};
  }

  auto cross = cross_product( a.direction_, b.direction_);

  return a.origin_ +
         (a.direction_ * (scalar_product( cross_product( diff, b.direction_),
                                          cross_product( a.origin_, diff)))
          / scalar_product( cross, cross));
}

}

#endif // TRIANGLES_3D_LINE_HH_
