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
    pqxx::connection con("dbname=testdb user=robertk");

    pqxx::work transaction(con);
    pqxx::result result = transaction.exec(R"(
      SELECT a, b FROM test
    )");

    std::vector<int> as;
    for (unsigned int i = 0; i < result.size(); i++) {
      as.push_back(result[i][0].as<int>());
    }

    std::cout << "The a's in the database are: \n\n";
    for (const auto &el : as) {
      std::cout << crayon(std::to_string(el), "blue") << std::endl;
    }

    transaction.commit();
  }
}

