#include "utils.h"

namespace cpp_postgres_app {
  std::vector<std::string> cstring_to_vector(int argc, char **argv) {
    std::vector<std::string> out;

    if (argc < 0) {
      throw invalid_string_length();
    }

    for (unsigned int i = 0; i < argc; ++i) {
      out.push_back(argv[i]);
    }

    return(out);
  }
}

