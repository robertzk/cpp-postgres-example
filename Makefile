app: main.o utils.o
	clang++ -o app.out main.o utils.o

main.o:
	clang++ -std=c++11 -Wall -g -c main.cpp

utils.o:
	clang++ -std=c++11 -Wall -g -c utils.cpp

clean:
	rm -f app.out main.o utils.o
