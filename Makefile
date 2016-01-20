app: main.o utils.o
	clang++ -o bin/app main.o utils.o

main.o:
	clang++ -std=c++11 -Wall -g -c src/main.cpp -o bin/main.o

utils.o:
	clang++ -std=c++11 -Wall -g -c src/utils.cpp

clean:
	rm -f bin/app bin/main.o bin/utils.o

