# C++ Postgres Example App

This shows an example application using the Postgres
[client interface](http://www.postgresql.org/docs/7.2/static/libpqplusplus.html)
to write from and read to a database.

## Development cycle

The typical development cycle is to compile the application and restart it:

```bash
make clean && make && bin/app
```

Ensure you have installed and linked [libpqxx](http://pqxx.org/development/libpqxx/) with the header files present in `/usr/local/include`.

### License

This project is licensed under the MIT License:

Copyright (c) 2016 Robert Krzyzanowski

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Authors

This project was created by Robert Krzyzanowski, rob@syberia.io.

