#ifndef CPP_POSTGRES_APP_UTILS_H
#define CPP_POSTGRES_APP_UTILS_H

#include <vector>
#include <string>

namespace cpp_postgres_app {
  struct invalid_string_length {};

  /* Convert C-style strings to a std::vector.
   *
   * @param argc. Argument count. 
   * @param argv. Pointer to C-style strings.
   * @return A std::vector representing the converted strings. */
  std::vector<std::string> cstring_to_vector(int argc, char **argv);

  /* Convert a std::string to lowercase.
   *
   * @param str. The string to convert.
   * @return A std::string in lowercase.
   */
  std::string tolower(const std::string &str);
}

#endif

