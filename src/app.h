#ifndef CPP_POSTGRES_APP_APP_H
#define CPP_POSTGRES_APP_APP_H
#include "utils.h"
#include "color.h"
#include <iostream>

namespace cpp_postgres_app {
  /* Start the C++ Postgres app given command-line arguments.
   *
   * @param arguments. A vector of string arguments given in the command line.
   * @return A status code, 0 if no errors occurred during the run. */
  int start(const std::vector<std::string> &arguments);
}

#endif

