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
    : n_{cross_product( b - a, c - a).normalize()}, c_{-scalar_product(n_, a)} {}

  bool is_valid() const {
    return std::isfinite( c_) && n_.is_valid();
  }
};

template <typename T>
inline bool coincident( const Plane<T>& a, const Plane<T>& b) {
  return is_close( a.n_, b.n_) && is_close( a.c_, b.c_);
}

template <typename T>
inline Line<T> get_intersection( const Plane<T>& a, const Plane<T>& b) {
  T n_a_square = scalar_product( a.n_, a.n_);
  T n_b_square = scalar_product( b.n_, b.n_);
  T product    = scalar_product( a.n_, b.n_);
  T denom      = n_a_square * n_b_square - product * product;

  return Line<T>{(b.c_ * product - a.c_ * n_b_square) / denom * a.n_ +
                 (a.c_ * product - b.c_ * n_a_square) / denom * b.n_,
                 cross_product( a.n_, b.n_)};
}

}

#endif // TRIANGLES_3D_PLANE_HH_
