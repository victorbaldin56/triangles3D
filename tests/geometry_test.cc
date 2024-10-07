#include <utility>

#include <gtest/gtest.h>

#include "triangle.hh"

using namespace geometry;

TEST( points, is_close) {
  ASSERT_FALSE( is_close( Point<float>{1, 2, 0}, Point<float>{1, 2, 1}));
  ASSERT_TRUE( is_close( Point<float>{1, 2, 3}, Point<float>{1, 2, 1 + 2}));
}

TEST( points, cross_product) {
  ASSERT_TRUE( is_close( cross_product( Point<float>{1, 1, 1}, Point<float>{2, 2, 2}),
                                        Point<float>{0, 0, 0}));
  ASSERT_TRUE( is_close( cross_product( Point<float>{1, 0, 0}, Point<float>{0, 1, 0}),
                                        Point<float>{0, 0, 1}));
}

TEST( points, normalize) {
  auto n_x = 1 / std::sqrt( 3.f);
  ASSERT_TRUE( is_close( Point<float>{1, 1, 1}.normalize(), Point<float>{n_x, n_x, n_x}));
}

// test plane construction from 3 points
TEST( planes, ctor) {
  // sanity test (3 points that do not define a plane)
  ASSERT_FALSE( (Plane<float>{}.is_valid()));
  ASSERT_FALSE( (Plane<float>{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}.is_valid()));
  ASSERT_FALSE( (Plane<float>{{1, 2, 0}, {0, 0, 0}, {0, 0, 0}}.is_valid()));
  ASSERT_FALSE( (Plane<float>{{1.2, 2.2, 4}, {2.4, 4.4, 8}, {6, 11, 20}}.is_valid()));

  // normal tests
  Plane<float> p1{{1, 2, 3}, {4, 0, 1}, {2, -1, 5}};
  Plane<float> p2{10, 8, 7, 47};

  Plane<float> p3{{0, 0, 0}, {1, 1, 1}, {2, 1, 0}};
  Plane<float> p4{1, -2, 1, 0};

  ASSERT_TRUE( p1.is_valid());
  ASSERT_TRUE( p2.is_valid());
  ASSERT_TRUE( p3.is_valid());
  ASSERT_TRUE( p4.is_valid());

  ASSERT_TRUE( coincident( p1, p2));
  ASSERT_TRUE( coincident( p3, p4));
}

TEST( planes, intersection) {
  Plane<float> p1{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
  ASSERT_FALSE( get_intersection( p1, Plane<float>{{0, 0, 1}, {1, 0, 1}, {0, 1, 1}}).is_valid());

  Plane<float> p2{{0, 0, 0}, {1, 0, 0}, {0, 0, 1}};
  auto l12 = get_intersection( p1, p2);

  ASSERT_TRUE( l12.is_valid());
  ASSERT_TRUE( coincident( l12, Line<float>{{1, 0, 0}, {0, 0, 0}}));

  Point<float> a{8.9, 100.1, 90.9};
  Point<float> b{11, 11.1, 11.11};

  Plane<float> p3{b, a, {0, 0, 0}};
  Plane<float> p4{a, b, {1e-5, 99, 0.4}};
  auto l34 = get_intersection( p3, p4);

  ASSERT_TRUE( l34.is_valid());
  ASSERT_TRUE( coincident( l34, Line<float>{a - b, a}));
}

TEST( triangles, intersection) {
  Triangle<float> t1{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
  Triangle<float> t2{{0, 0, -1}, {0, 0, 1}, {-100, -100, 0}};
  Triangle<float> t3{{6, 0, 3}, {-3, -4, 0}, {-3, 4, 0}};
  Triangle<float> t4{{0, -2, 4.2}, {0, 2, 4}, {0, 0, -10}};

  ASSERT_TRUE( have_intersection( t1, t2));
  ASSERT_TRUE( have_intersection( t3, t4));
}

int main( int argc, char** argv) {
  testing::InitGoogleTest( &argc, argv);
  return RUN_ALL_TESTS();
}
