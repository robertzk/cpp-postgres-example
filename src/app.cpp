#include "app.h"

namespace cpp_postgres_app {
  int start(const std::vector<std::string> &arguments) {
    const char* PGHOST = getenv("PGHOST");
    std::cout << "Hello world" << "\033[1;31mbold red text\033[0m\n";
    std::cout << "How's " << crayon("it going?", "green") << std::endl;
    for (const auto &el : arguments) {
      std::cout << std::endl << "\033[31m" << el << "\033[39m !!";
    }

    db_app();

    return 0;
  }

  void db_app() {

  }
}

