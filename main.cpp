#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  cout << "Hello world";
  for (const auto &el : cpp_postgres_app::cstring_to_vector(argc, argv)) {
    cout << std::endl << el;
  }
  return 0;
}

