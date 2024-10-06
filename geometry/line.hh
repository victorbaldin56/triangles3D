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

  bool is_valid() const {
    return direction_.is_valid() && origin_.is_valid();
  }

  bool coincident_with( const Line<T>& rhs) const {
    return collinear( direction_, rhs.direction_) &&
           collinear( origin_ - rhs.origin_, direction_);
  }

  Point<T> get_intersection( const Line<T>& rhs) const {
    if ( coincident_with( rhs) ) {
      return Point<T>{};
    }

    auto diff = rhs.origin_ - origin_;

    // skew case
    if ( !coplanar( diff, direction_, rhs.direction_) ) {
      return Point<T>{};
    }

    auto cross = cross_product( direction_, rhs.direction_);

    return origin_ +
          (direction_ * (scalar_product( cross_product( diff, rhs.direction_),
                                         cross_product( origin_, diff)))
          / scalar_product( cross, cross));

  }
};

template <typename T>
inline bool coincident( const Line<T>& a, const Line<T>& b) {
  return a.coincident_with( b);
}

template <typename T>
inline Point<T> get_intersection( const Line<T>& a, const Line<T>& b) {
  return a.get_intersection( b);
}

}

#endif // TRIANGLES_3D_LINE_HH_
