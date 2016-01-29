#include "pg_example_app.h"
#include "app.h"

namespace cpp_postgres_app {
  int start(const std::vector<std::string> &arguments) {
    
    start_db_write_repl();

    return 0;
  }

  void db_app(const std::string &pre_query) {
    pqxx::connection con("dbname=testdb user=robertk");

    pqxx::work transaction(con);

    pqxx::result pre_query_result= transaction.exec(pre_query);

    pqxx::result result = transaction.exec(R"(
      SELECT a, b FROM test
    )");

    std::string annotation[2] = {"a", "b"};
    for (unsigned int k = 0; k < 2; k++) {
      auto type = annotation[k];
      std::vector<int> i_els;
      std::vector<std::string> s_els;
      for (unsigned int i = 0; i < result.size(); i++) {
        if (k == 0) {
          i_els.push_back(result[i][k].as<int>());
        } else {
          s_els.push_back(result[i][k].as<std::string>());
        }
      }

      std::cout << "The " << type << "'s in the database are: \n\n";
      if (k == 0) {
        for (const auto &el : i_els) {
          std::cout << crayon(std::to_string(el), "blue") << std::endl;
        }
      } else {
        for (const auto &el : s_els) {
          std::cout << crayon(el, "red") << std::endl;
        }
      }
    }

    transaction.commit();
  }
}

