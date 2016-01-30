#include "pg_example_app.h"

namespace cpp_postgres_app {

   int start_db_write_repl() {
     std::string input;
     while (true) {
       std::cout << "Select a database table: ";
       std::cin  >> input;

       if (is_end_of_repl(input.c_str())) {
         break;
       }

       PgTable table { input };
       std::cout << table.to_s() << "\n";

       insert_and_display(table);
     }

     return 0;
   }

   bool is_end_of_repl(const char* input) {
     return strcmp(input, "\\q") == 0;
   }

   int insert_and_display(PgTable &table) {
     pqxx::connection con("dbname=testdb user=robertk");
 
     pqxx::work transaction(con);

     std::vector<std::string> column_names { table.column_names() };
     std::map<std::string, PgTable::ColumnType> column_types = table.column_map(); 

     std::cout << "Enter a new row to insert (or \\q): ";
     std::string row;
     std::cin.ignore(); // http://stackoverflow.com/questions/6649852/getline-not-working-properly-what-could-be-the-reasons
     std::getline(std::cin, row);

     if (!is_end_of_repl(row.c_str())) {
       pqxx::result pre_query_result = transaction.exec(table.insert_by_csv(row));
     }
     std::cout << std::endl;

     std::string select_query { "SELECT " };
     bool first = true;
     for (const auto &el : column_names) { select_query += (first ? "" : ", ") + el; first = false; }
     select_query += " FROM " + table.table_name() + ';';

     pqxx::result result = transaction.exec(select_query);
     
     for (unsigned int k = 0; k < column_names.size(); k++) {
       auto type = column_types[column_names[k]];
       std::cout << "The " << column_names[k] << "'s in the database are: \n";
       for (unsigned int i = 0; i < result.size(); i++) {
         if (type == PgTable::ColumnType::Int) {
           std::cout << crayon(std::to_string(result[i][k].as<int>()), "blue") << "\n";
         } else {
           std::cout << crayon(result[i][k].as<std::string>(), "red") << "\n";
         }
       }
     }
 
     transaction.commit();
     return 0;
   }
}

