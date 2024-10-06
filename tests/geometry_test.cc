#include <gtest/gtest.h>

#include "triangle.hh"

// test plane construction from 3 points
TEST( geometry, plane) {
  EXPECT_FALSE( geometry::Plane<float>{}.is_valid());
}

int main( int argc, char** argv) {
  testing::InitGoogleTest( &argc, argv);
  return RUN_ALL_TESTS();
}
