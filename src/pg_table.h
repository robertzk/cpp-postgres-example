#ifndef CPP_POSTGRES_APP_PG_TABLE_H
#define CPP_POSTGRES_APP_PG_TABLE_H

#include <stdint.h>
#include <assert.h>
#include <utility> // for std::pair
#include <string>
#include <iostream>
#include <sstream>
#include <pqxx/pqxx>
#include "color.h"
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

    static ColumnType str_to_column_type(const std::string &str) {
      if (strcmp(str.c_str(), "int") == 0) {
        return ColumnType::Int;
      } else {
        return ColumnType::String;
      }
    }

    static const std::string column_type_to_str(ColumnType t) {
      if (t == ColumnType::Int) {
        return std::string { "int" };
      } else {
        return std::string { "string" };
      }
    }

    /* Construct an object representing a database table and its
     * column names and types.
     *
     * A \code{name} in the form "table(col1 : type, col2 : type, ...)"
     * will be parsed into column type information and marked complete.
     *
     * @param _name Name of the database table.
     */
    PgTable(const std::string &_name); 

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
     * @param order The order of the keys to insert, by default the
     *   same as the insert order for the table.
     * @return The query to insert this record into the table as a string.
     */
    const std::string insert_by_csv(const std::string &row) {
      return insert_by_csv(row, insert_order);
    }
    const std::string insert_by_csv(const std::string &row,
        std::vector<std::string> &order) {
      if (!complete) {
        throw PgTableIncompleteDefinition();
      }

      std::stringstream query;
      query << "INSERT INTO " << name << '(';
      bool first = true;
      for (const auto &column_el : order) {
        query << (first ? "" : ",") << column_el;
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
        
        switch(columns[order[count]]) {
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

    /* A string representation of a database tab;e.
     *
     * @return A string of table name and column name / type pairs. */
    const std::string to_s();

    /* Parse a table's name / type representation from a simple description.
     *
     * @param description Can be either the name of the type, or of
     *   the form "table(col1 : type, col2 : type, ...)".
     * @param table A pointer to the table to initialize using the parsed string.
     * @return The name of the parsed table. Columns will be added using
     *   the \code{add_column} method. */
    static std::string parse(const std::string &expression, PgTable *table) {
      std::string name;
      char c;
      unsigned int i = 0;

      for (; expression[i] && expression[i] != '('; ++i) {
        name += expression[i];
      }

      if (expression[i]) {
        assert(expression[i] == '(');

        while (expression[i] != ')') {
          ++i;
          std::string column_name;
          for (; expression[i] && expression[i] != ':'; ++i) {
            column_name += expression[i];
          }
          assert(expression[i] == ':');
          ++i;
          std::string column_type;
          for (; expression[i] && expression[i] != ',' && expression[i] != ')'; ++i) {
            column_type += expression[i];
          }
          table->add_column(column_name, PgTable::str_to_column_type(column_type));
        }
      }

      return name;
    }

    /* The name of the table.
     *
     * @return The name of the table. */
    const std::string table_name() const { return name; }

    /* The column names on the table.
     *
     * @return A vector of column names on the table. */
    const std::vector<std::string> column_names() const { return insert_order; }

    /* The column types on the table.
     *
     * @return A vector of column names on the table. */
    const std::vector<ColumnType> column_types() const {
      std::vector<ColumnType> column_types;
      for (const auto el : columns) {
        column_types.push_back(el.second);
      }
      return column_types;
    }

    /* The column map.
     *
     * @return A map of column names and types. */
    const std::map<std::string, ColumnType> column_map() const { return columns; }

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

