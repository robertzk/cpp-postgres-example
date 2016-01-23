#ifndef CPP_POSTGRES_APP_PG_TABLE_H
#define CPP_POSTGRES_APP_PG_TABLE_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <sstream>
#include <pqxx/pqxx>
//#include "pg_element.h"

namespace cpp_postgres_app {
  struct PgTableInvalidLength {};
  struct PgTableColumnExists {};
  struct PgTableIncompleteDefinition{};

  /* Represent a PG table. */
  class PgTable {
  public:
    enum class ColumnType {
      Int, String
    };

    /* Construct an object representing a database table and its
     * column names and types.
     *
     * @param _name Name of the database table.
     */
    PgTable(std::string _name) : name(_name), complete(false) {
      if (name.length() == 0) {
        throw PgTableInvalidLength();
      }
    }

    /* Add a new column to the table definition.
     *
     * @param name The name of the column.
     * @param type The type of the column: must be either
     *   \code{PgTable::ColumnType::Int} or
     *   \code{PgTable::ColumnType::String}.
     */
    bool add_column(std::string name, ColumnType type) {
      if (columns.find(name) != columns.end()) {
        throw PgTableColumnExists();
      }
      columns[name] = type;
      insert_order.push_back(name);
      return true;
    }

    /* Mark a table as being completely determined.
     * 
     * A table is completely determined when its columns have
     * all been specified.
     *
     * @return Nothing, but set the internal \code{complete}
     *   flag to true.
     */
    void mark_complete() { complete = true; }
    
    /* Insert a record using a comma-separated string.
     *
     * @param row The row to insert as a comma-separated string.
     *   Note that no spaces are currently allowed.
     * @return 1 if successful, 0 otherwise.
     */
    int insert_by_csv(std::string row) {
      if (!complete) {
        throw PgTableIncompleteDefinition();
      }
      
      //std::vector<char> buffer;
      int count = 0;
      for (unsigned int i = 0; row[i]; ++i) {
        std::stringstream ss;
        for (; row[i] && row[i] != ','; ++i) {
          ss << row[i];
        }
        
        switch(columns[insert_order[count]]) {
          case ColumnType::Int: 
            int_least32_t el;
            ss >> el;
            std::cout << "Int: " << i << " " << el << std::endl;
            break;
          case ColumnType::String:
            std::string el2 = ss.str();
            std::cout << "String: " << i << " " << el2 << std::endl;
           break;
        }
        count++;
      }

      return 1;
    }

  private:

    bool complete;

    std::string name;

    /* A map representing the names of 
     * columns and the type of a column.
     */
    std::map<std::string, ColumnType> columns;
    std::vector<std::string> insert_order;
  };
}

#endif

