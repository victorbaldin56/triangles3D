#ifndef TRIANGLES_3D_LINE_HH_
#define TRIANGLES_3D_LINE_HH_

#include "point.hh"

namespace geometry {

template <typename T>
struct Line {
  Point<T> direction_, origin_;

  Line() : direction_{}, origin_{} {}
  Line( const Point<T>& a, const Point<T>& b) : direction_{a - b}, origin_{a} {}

  bool is_valid() const {
    return is_close( direction_, Point<T>{});
  }
};

template <typename T>
inline Point<T> get_intersection( const Line<T>& a, const Line<T>& b) {

}

}

#endif // TRIANGLES_3D_LINE_HH_
