#include "app.h"

int main(int argc, char **argv) {
  return cpp_postgres_app::start(cpp_postgres_app::cstring_to_vector(argc, argv) );
}

