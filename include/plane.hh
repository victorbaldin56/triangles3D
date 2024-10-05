#ifndef TRIANGLES_3D_PLANE_HH_
#define TRIANGLES_3D_PLANE_HH_

#include "line.hh"

namespace geometry {

template <typename T>
struct Plane {
  Point<T> n_;
  T        c_;

  Plane() : n_{}, c_{} {}
  Plane( const Point<T>& a, const Point<T>& b, const Point<T>& c)
    : n_{vector_product( b - a, c - a)}, c_{-scalar_product(n_, a)} {}
};

template <typename T>
inline Line<T> get_intersection( const Plane<T>& a, const Plane<T>& b) {
  Line<T> res;

  T n_a_square = scalar_product( a.n_, a.n_);
  T n_b_square = scalar_product( b.n_, b.n_);
  T product    = scalar_product( a.n_, b.n_);
  T denom      = n_a_square * n_b_square - product * product;

  // planes are parallel or coincident
  if ( is_close(denom, 0) ) {
    return Line<T>{};
  }

  return Line<T>{(b.c_ * product - a.c_ * n_b_square) / denom * a.n_ +
                 (a.c_ * product - b.c_ * n_a_square) / denom * b.n_,
                 vector_product( a.n_, b.n_)};
}

}

#endif // TRIANGLES_3D_PLANE_HH_
