#include "utils.h"
#include "color.h"
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;
using namespace cpp_postgres_app;

int main(int argc, char **argv) {
  cout << "Hello world" << "\033[1;31mbold red text\033[0m\n";
  cout << "How's " << crayon("it going?", "green") << std::endl;
  for (const auto &el : cstring_to_vector(argc, argv)) {
    cout << std::endl << "\033[31m" << el << "\033[39m !!";
  }
  return 0;
}

