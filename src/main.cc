#include <iostream>
#include <set>
#include <vector>

#include "triangle.hh"

int main() {
  std::size_t count = 0;
  std::cin >> count;

  std::vector<geometry::Triangle<float>> triangles( count);
  for ( auto& t : triangles ) {
    std::cin >> t;
  }

  std::set<std::size_t> ans;

  for ( std::size_t i = 0; i < triangles.size(); ) {
    for ( std::size_t j = ++i; j < triangles.size(); ++j) {
      if ( geometry::have_intersection( triangles[i], triangles[j]) ) {
        ans.insert( i);
        ans.insert( j);
      }
    }
  }

  for ( std::size_t n : ans ) {
    std::cout << n << "\n";
  }

  return 0;
}
