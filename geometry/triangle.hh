#ifndef TRIANGLES_3D_TRIANGLE_HH_
#define TRIANGLES_3D_TRIANGLE_HH_

#include "plane.hh"
#include "segment.hh"

namespace geometry {

template <typename T>
struct Triangle {
  Point<T> a_, b_, c_;

  Triangle() : a_{}, b_{}, c_{} {}
  Triangle( const Point<T>& a, const Point<T>& b, const Point<T>& c)
    : a_{a}, b_{b}, c_{c} {}

  Plane<T> plane() const {
    return Plane<T>{a_, b_, c_};
  }

  bool intersects_with( const Line<T>& line) const {
    Segment<T> ab{a_, b_};
    Segment<T> bc{b_, c_};
    Segment<T> ac{a_, c_};
    return ab.intersects( line) || bc.intersects( line) || ac.intersects( line);
  }

  T area() const {
    return cross_product( c_ - a_, b_ - a_).length() / 2;
  }

  bool contains( const Point<T>& point) const {
    return is_close( Triangle<T>{a_, b_, point}.area() +
                     Triangle<T>{a_, c_, point}.area() +
                     Triangle<T>{b_, c_, point}.area(), area());
  }
};

template <typename T>
inline bool have_intersection_in_plane( const Triangle<T>& a, const Triangle<T>& b) {
  return a.contains( b.a_) || a.contains( b.b_) || a.contains( b.c_);
}

template <typename T>
inline bool have_intersection( const Triangle<T>& a, const Triangle<T>& b) {
  auto plane_a = a.plane();
  auto plane_b = b.plane();

  // coincident planes case
  if ( coincident( plane_a, plane_b) ) {
    return have_intersection_in_plane( a, b);
  }

  auto intersection = get_intersection( plane_a, plane_b);

  // parallel & non-coincident planes case
  if ( !intersection.is_valid() ) {
    return false;
  }
  return a.intersects_with( intersection) && b.intersects_with( intersection);
}

template <typename T>
std::istream& operator>>( std::istream& is, Triangle<T>& p) {
  Point<T> a, b, c;
  std::cin >> a >> b >> c;
  p = Triangle<T>{a, b, c};
  return is;
}

}

#endif // TRIANGLES_3D_TRIANGLE_HH_
