all: server

server: main.cpp Controller/MainConstants.h Controller/MainConstants.cpp
	g++ -pthread main.cpp Controller/MainConstants.h Controller/MainConstants.cpp -o server

clean:
	rm -f server
