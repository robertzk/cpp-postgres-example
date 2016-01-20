# Thanks to http://stackoverflow.com/a/21355129
# make       -> compile the application
# make clean -> remove the application and all object files (.o)
# make all   -> clean and compile
APPNAME  = app
SRC      = src/main.cpp  \
					 src/app.cpp   \
           src/utils.cpp \
					 src/color.cpp
# Compilation options
#CXXFLAGS  = -O2 -g -W -Wall -Wno-unused-parameter -fPIC
CXXFLAGS = -std=c++11 -g
LDFLAGS  = -I/usr/local/include/ -lpqxx -lpq

# How to compile individual object files
OBJS    = $(SRC:.cpp=.o)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

# Library compilation
$(APPNAME): $(OBJS) $(SRC)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(APPNAME)
	mv $(APPNAME) bin/$(APPNAME)

# Cleaning rule
clean:
	rm -f $(OBJS) $(APPNAME) *~
	rm -f src/*.o

# additional rule
all: clean main

