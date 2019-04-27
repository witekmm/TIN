all: server

server: main.cpp Controller/MainInput.h Controller/MainInput.cpp Controller/MainConstants.h Controller/MainConstants.cpp
	g++ -pthread main.cpp Controller/MainInput.h Controller/MainInput.cpp Controller/MainConstants.h Controller/MainConstants.cpp -o server 

clean:
	rm -f server
