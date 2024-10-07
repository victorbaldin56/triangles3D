#ifndef TRIANGLES_3D_POINT_HH_
#define TRIANGLES_3D_POINT_HH_

#include <iostream>

#include "float.hh"

namespace geometry {

template <typename T>
struct Point {
  static_assert( std::numeric_limits<T>::is_iec559,
                 "Unsupported floating-point representation");
  static_assert( std::numeric_limits<T>::has_quiet_NaN,
                 "Unsupported numeric type");

  T x_, y_, z_; // coordinates in 3D

  // default-constructed point is "invalid"
  Point( T x = NAN, T y = NAN, T z = NAN) : x_{x}, y_{y}, z_{z} {}

  // in case of domain error we can leave point in "invalid" state
  bool isValid() const {
    return std::isfinite( x_) && std::isfinite( y_) && std::isfinite( z_);
  }

  Point<T>& operator+=( const Point<T>& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
  }

  Point<T>& operator-=( const Point<T>& rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
  }

  Point<T>& operator*=( T rhs) {
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;
    return *this;
  }

  Point<T>& operator/=( T rhs) {
    x_ /= rhs;
    y_ /= rhs;
    z_ /= rhs;
    return *this;
  }

  T length() const {
    return std::hypot( x_, y_, z_);
  }

  Point<T>& normalize() {
    (*this) /= length();
    return *this;
  }

  static Point<T> zeroVector() {
    return Point<T>{0, 0, 0};
  }
};

template <typename T>
inline bool isClose( const Point<T>& a, const Point<T>& b) {
  return isClose( a.x_, b.x_) && isClose( a.y_, b.y_) && isClose( a.z_, b.z_);
}

template <typename T>
inline Point<T> operator+( const Point<T>& a, const Point<T>& b) {
  return (Point<T>{a} += b);
}

template <typename T>
inline Point<T> operator-( const Point<T>& a, const Point<T>& b) {
  return (Point<T>{a} -= b);
}

template <typename T>
inline Point<T> operator*( const Point<T>& a, T k) {
  return (Point<T>{a} *= k);
}

template <typename T>
inline Point<T> operator*( T k, const Point<T>& a) {
  return a * k;
}

template <typename T>
inline Point<T> operator/( const Point<T>& a, T k) {
  return (Point<T>{a} /= k);
}

template <typename T>
inline Point<T> operator+( const Point<T>& a) {
  return a;
}

template <typename T>
inline Point<T> operator-( const Point<T>& a) {
  return static_cast<T>(-1) * a;
}

template <typename T>
inline T scalarProduct( const Point<T>& a, const Point<T>& b) {
  return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_;
}

template <typename T>
inline Point<T> crossProduct( const Point<T>& a, const Point<T>& b) {
  return Point<T>{a.y_ * b.z_ - a.z_ * b.y_,
                  a.z_ * b.x_ - a.x_ * b.z_,
                  a.x_ * b.y_ - a.y_ * b.x_};
}

template <typename T>
inline T tripleProduct( const Point<T>& a, const Point<T>& b, const Point<T>& c) {
  T k1 = a.y_ * b.z_ - a.z_ * b.y_;
  T k2 = a.z_ * b.x_ - a.x_ * b.z_;
  T k3 = a.x_ * b.y_ - a.y_ * b.x_;
  return k1 * c.x_ + k2 * c.y_ + k3 * c.z_;
}

template <typename T>
inline bool collinear( const Point<T>& a, const Point<T>& b) {
  return isClose( crossProduct( a, b), Point<T>::zeroVector());
}

template <typename T>
inline bool coplanar( const Point<T>& a, const Point<T>& b, const Point<T>& c) {
  return isClose( tripleProduct( a, b, c), static_cast<T>(0));
}

template <typename T>
std::istream& operator>>( std::istream& is, Point<T>& p) {
  T x, y, z;
  std::cin >> x >> y >> z;
  p = Point<T>{x, y, z};
  return is;
}

}

#endif // TRIANGLES_3D_POINT_HH_
