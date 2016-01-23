#include "app.h"

namespace cpp_postgres_app {
  int start(const std::vector<std::string> &arguments) {
    const char* PGHOST = getenv("PGHOST");
    std::cout << "Hello world" << "\033[1;31mbold red text\033[0m\n";
    std::cout << "How's " << crayon("it going?", "green") << std::endl;
    for (const auto &el : arguments) {
      std::cout << std::endl << "\033[31m" << el << "\033[39m !!\n\n";
    }

    // Mucking around with PgTable
    PgTable *table = new PgTable(std::string { "test" });
    table->add_column("a", PgTable::ColumnType::Int);
    table->add_column("b", PgTable::ColumnType::String);
    table->mark_complete();

    std::cout << "\n\n";
    db_app(table->insert_by_csv("1,foo"));

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

