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

  std::string tolower(const std::string &str) {
    // http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
    std::string lowerstr = std::string { str };
    std::transform(lowerstr.begin(), lowerstr.end(),
                   lowerstr.begin(), ::tolower);
    return lowerstr;
  }
}

