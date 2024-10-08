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

  bool intersects( const Line<T>& line) const {
    Segment<T> ab{a_, b_};
    Segment<T> bc{b_, c_};
    Segment<T> ac{a_, c_};
    return ab.intersects( line) || bc.intersects( line) || ac.intersects( line);
  }

  T area() const {
    return crossProduct( c_ - a_, b_ - a_).length() / 2;
  }

  bool contains( const Point<T>& point) const {
    return isClose( Triangle<T>{a_, b_, point}.area() +
                    Triangle<T>{a_, c_, point}.area() +
                    Triangle<T>{b_, c_, point}.area(), area());
  }

  Segment<T> toSegment() const {
    if ( !collinear( a_ - b_, c_ - b_) ) {
      return Segment<T>{};
    }

    if ( scalarProduct( a_ - b_, c_ - b_) <= 0 ) {
      return Segment<T>{a_, c_};
    }
    if ( scalarProduct( a_ - c_, b_ - c_) <= 0 ) {
      return Segment<T>{a_, b_};
    }
    return Segment<T>{b_, c_};
  }
};

template <typename T>
inline bool intersectInPlane( const Triangle<T>& a, const Triangle<T>& b) {
  return a.contains( b.a_) || a.contains( b.b_) || a.contains( b.c_);
}

template <typename T>
inline bool intersect( const Triangle<T> t, const Segment<T> s ) {
  auto inter_pt = t.plane().getIntersection( s.getLine());
  if ( !inter_pt.valid() ) {
    return false;
  }
  return t.contains( inter_pt);
}

template <typename T>
inline bool intersect( const Triangle<T>& a, const Triangle<T>& b) {
  auto segment_a = a.toSegment();
  auto segment_b = b.toSegment();

  if ( segment_a.valid() && segment_b.valid() ) {
    return segment_a.intersects( segment_b);
  }
  if ( segment_a.valid() ) {
    return intersect( a, segment_b);
  }
  if ( segment_b.valid() ) {
    return intersect( b, segment_a);
  }

  auto plane_a = a.plane();
  auto plane_b = b.plane();

  // coincident planes case
  if ( coincident( plane_a, plane_b) ) {
    return intersectInPlane( a, b);
  }

  auto inter_line = getIntersection( plane_a, plane_b);

  // parallel & non-coincident planes case
  if ( !inter_line.valid() ) {
    return false;
  }
  return a.intersects( inter_line) && b.intersects( inter_line);
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
