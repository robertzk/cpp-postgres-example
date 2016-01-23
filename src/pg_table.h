#include <string>
#include <pqxx/pqxx>
//#include "pg_element.h"

namespace cpp_postgres_app {
  struct PgTableInvalidLength {};
  struct PgTableColumnExists {};

  /* Represent a PG table. */
  class PgTable {
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
      if (columns.find(name) == columns.end()) {
        throw PgTableColumnExists();
      }
      columns[name] = type;
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

  private:

    bool complete;

    std::string name;

    /* A map representing the names of 
     * columns and the type of a column.
     */
    std::map<std::string, ColumnType> columns;
  };
}

