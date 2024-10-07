#ifndef TRIANGLES_3D_FLOAT_HH_
#define TRIANGLES_3D_FLOAT_HH_

#include <cmath>
#include <limits>

namespace geometry {

template <typename T>
inline bool isClose( T x, T y) {
  return std::fabs( x - y) <= 1e-5; // FIXME
}

}

#endif // TRIANGLES_3D_FLOAT_HH_
