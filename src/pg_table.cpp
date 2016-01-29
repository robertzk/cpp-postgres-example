#include "pg_table.h"

namespace cpp_postgres_app {

  PgTable::PgTable(const std::string &_name) {
    if (_name.length() == 0) {
      throw PgTableInvalidLength();
    }

    name = PgTable::parse(_name, this);
    this->mark_complete();
  }

  const std::string PgTable::to_s() {
    std::string s { "" };
    s += crayon(name, "green") + " (";
    bool first = true;
    for (const auto &colname : insert_order) {
      s += (first ? "" : ", ") + crayon(colname, "yellow") + " : " +
        crayon(PgTable::column_type_to_str(columns[colname]), "blue");
      first = false;
    } 
    s += ")";
    return s;
  }

}


