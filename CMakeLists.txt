cmake_minimum_required( VERSION 3.14)
project( "triangles3D")

add_library( geometry INTERFACE)
target_include_directories( geometry INTERFACE include)

add_executable( test main.cc)
target_link_libraries( test geometry)
