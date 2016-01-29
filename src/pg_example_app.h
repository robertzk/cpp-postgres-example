#ifndef CPP_POSTGRES_APP_PG_EXAMPLE_APP_H
#define CPP_POSTGRES_APP_PG_EXAMPLE_APP_H
#include <iostream>
#include <string>
#include <map>
#include "pg_table.h"

namespace cpp_postgres_app {

  /* Write entries to a given database table interactively.
   *
   * This function will initiate a REPL loop and requires no arguments
   * to commence its operation.
   *
   * @return A status code, 0 if no errors occurred during the run. */
   int start_db_write_repl();

   /* Whether or not the string corresponds to the '\q' end of REPL character.
    *
    * @return True if end of REPL, false otherwise. */
   bool is_end_of_repl(const char* input);

   /* Insert values into a table using a loop.
    *
    * @param table A reference to the table object giving the type information
    *   in the table.
    * @return A status code, 0 if no errors occurred during the run. */
   int start_table_insert_loop(PgTable &table);
}

#endif

