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
    : n_{cross_product( b - a, c - a).normalize()}, d_{scalar_product( n_, a)} {}

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

  // https://en.wikipedia.org/wiki/Plane%E2%80%93plane_intersection
  Line<T> get_intersection( const Plane<T>& rhs) const {
    T dot = scalar_product( n_, rhs.n_);
    T dnm = 1 - dot * dot;
    T c1 = (d_ - rhs.d_ * dot) / dnm;
    T c2 = (rhs.d_ - d_ * dot) / dnm;

    return Line<T>{cross_product( n_, rhs.n_),
                   c1 * n_ + c2 * rhs.n_};
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
