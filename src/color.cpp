#include "color.h"

namespace cpp_postgres_app {
  std::string crayon(const std::string &message, const std::string &color) {
    return colored_output(message, colored_output_class(color));
  }

  std::string colored_output(const std::string &message, ColorOutput color) {
    std::stringstream ss;
    ss << "\033[1;" << std::to_string((int)color.to_char())
       << 'm' << message << "\033[0m";
    return ss.str();
  }

  ColorOutput colored_output_class(const std::string &color) {
    std::string sane_color = tolower(std::string { color });

    if (sane_color.compare(std::string { "red" }) == 0) {
      return ColorOutput { ColorOutput::red };
    }

    if (sane_color.compare(std::string { "green" }) == 0) {
      return ColorOutput { ColorOutput::green };
    }

    if (sane_color.compare(std::string { "yellow" }) == 0) {
      return ColorOutput { ColorOutput::yellow };
    }

    if (sane_color.compare(std::string { "blue" }) == 0) {
      return ColorOutput { ColorOutput::blue };
    }

    if (sane_color.compare(std::string { "magenta" }) == 0) {
      return ColorOutput { ColorOutput::magenta };
    }

    if (sane_color.compare(std::string { "cyan" }) == 0) {
      return ColorOutput { ColorOutput::cyan };
    }

    if (sane_color.compare(std::string { "white" }) == 0) {
      return ColorOutput { ColorOutput::white };
    }

    if (sane_color.compare(std::string { "silver" }) == 0) {
      return ColorOutput { ColorOutput::silver };
    }

    throw invalid_colored_output_class();
  }
}

