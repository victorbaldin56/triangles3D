#ifndef TRIANGLES_3D_PLANE_HH_
#define TRIANGLES_3D_PLANE_HH_

#include "line.hh"

namespace geometry {

template <typename T>
class Plane {
  Point<T> n_;
  T        d_;

 public:
  Plane() : n_{}, d_{} {}
  Plane( const Point<T>& a, const Point<T>& b, const Point<T>& c)
    : n_{cross_product( b - a, c - a).normalize()}, d_{-scalar_product( n_, a)} {}

  // constructs plane ax + by + cz + d = 0
  Plane( T a, T b, T c, T d) {
    Point<T> n{a, b, c};
    T len = n.length();
    n_ = n / len;
    d_ = d / len;
  }

  bool is_valid() const {
    return std::isfinite( d_) && n_.is_valid();
  }

  bool coincident_with( const Plane<T>& rhs) const {
    return (is_close( n_, rhs.n_) && is_close( d_, rhs.d_)) ||
           (is_close( n_, -rhs.n_) && is_close( d_, -rhs.d_));
  }

  Line<T> get_intersection( const Plane<T>& rhs) const {
    T n_a_square = scalar_product( n_, n_);
    T n_b_square = scalar_product( rhs.n_, rhs.n_);
    T product    = scalar_product( n_, rhs.n_);
    T denom      = n_a_square * n_b_square - product * product;

    return Line<T>{(rhs.d_ * product - d_ * n_b_square) / denom * n_ +
                  (d_ * product - rhs.d_ * n_a_square) / denom * rhs.n_,
                  cross_product( n_, rhs.n_)};
  }
};

template <typename T>
inline bool coincident( const Plane<T>& a, const Plane<T>& b) {
  return a.coincident_with( b);
}

template <typename T>
inline Line<T> get_intersection( const Plane<T>& a, const Plane<T>& b) {
  return a.get_intersection( b);
}

}

#endif // TRIANGLES_3D_PLANE_HH_
