#ifndef TRIANGLES_3D_FLOAT_HH_
#define TRIANGLES_3D_FLOAT_HH_

#include <cmath>
#include <limits>

namespace geometry {

template <typename T>
inline bool isClose( T x, T y) {
  return std::fabs( x - y) <= std::numeric_limits<T>::epsilon();
}

}

#endif // TRIANGLES_3D_FLOAT_HH_
