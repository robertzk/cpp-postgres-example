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
    PgTable(const std::string &_name) : name(_name), complete(false) {
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
    bool add_column(const std::string &name, const ColumnType type) {
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
     * @return The query to insert this record into the table as a string.
     */
    const std::string insert_by_csv(const std::string &row) {
      if (!complete) {
        throw PgTableIncompleteDefinition();
      }
      

      std::stringstream query;
      query << "INSERT INTO " << name << '(';
      bool first = true;
      for (const auto &column_el : columns) {
        query << (first ? "" : ",") << column_el.first;
        first = false;
      }
      query << ") VALUES (";

      first = true;
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
            // std::cout << el;
            query << (count == 0 ? "" : ",") << el;
            break;
          case ColumnType::String:
            std::string el2 = ss.str();
            // std::cout << el2;
            query << (count == 0 ? "" : ",") << '\'' << el2 << '\'';
            break;
        }
        count++;
      }
      query << ");";

      return query.str();
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

