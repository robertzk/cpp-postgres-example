#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  cout << "Hello world" << "\033[1;31mbold red text\033[0m\n";
  for (const auto &el : cpp_postgres_app::cstring_to_vector(argc, argv)) {
    cout << std::endl << "\033[31m" << el << "\033[39m !!";
  }
  return 0;
}

