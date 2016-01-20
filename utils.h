#include <vector>
#include <string>

namespace cpp_postgres_app {
  struct invalid_string_length {};

  /* Convert C-style strings to a std::vector.
   *
   * @param argc Argument count. 
   * @param argv Pointer to C-style strings.
   * @return A std::vector representing the converted strings. */
  std::vector<std::string> cstring_to_vector(int argc, char **argv);
}

