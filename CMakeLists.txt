cmake_minimum_required( VERSION 3.14)
project( "triangles3D")

add_library( geometry INTERFACE)
target_include_directories( geometry INTERFACE geometry)

add_executable( main src/main.cc)
target_link_libraries( main geometry)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        "origin/main"
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable( geomtest tests/geometry_test.cc)
target_link_libraries( geomtest gtest_main;geometry)

add_test( NAME "UnitTest" COMMAND ${CMAKE_BINARY_DIR}/geomtest)
