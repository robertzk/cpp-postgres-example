#ifndef CPP_POSTGRES_APP_COLOR_H
#define CPP_POSTGRES_APP_COLOR_H

#include <algorithm>
#include <string>
#include <sstream>
#include "utils.h"

namespace cpp_postgres_app {
  
  // Colored enum class to print to the console.
  struct ColorOutput {
    enum color {
      red     = 31, green = 32, yellow = 33, blue   = 34,
      magenta = 35, cyan  = 36, white  = 37, silver = 90
    };

    color c;
    ColorOutput(color _c) : c(_c) { }
    char to_char() { return (char)c; }
  };

  struct invalid_colored_output_class {};

  /* Wrap a string with colored output for console printing.
   *
   * @param message. The message to transform into color.
   * @param color. The color to use. Must be one of 
   *   "red", "green", "yellow", "blue", "magenta", "cyan",
   *   "white", or "silver".
   * @return The \code{message} wrapped with codes necessary
   *   to turn it into the correct \code{color} when printed to
   *   the console. Will throw \code{invalid_colored_output_class}
   *   if an invalid color is passed.
   */
  std::string crayon(const std::string &message, const std::string &color);
  std::string colored_output(const std::string &message, ColorOutput color);

  /* Convert a color class to an integer.
   *
   * @param color. The color to use. Must be one of 
   *   "red", "green", "yellow", "blue", "magenta", "cyan",
   *   "white", or "silver".
   * @return A ColorOutput object representing the color. */
  ColorOutput colored_output_class(const std::string &color);
}

#endif

