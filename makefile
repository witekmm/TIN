all: client server

server: source/server/main.cpp
	g++ -pthread source/server/main.cpp -o server

client: source/client/main.cpp
	g++ -pthread source/client/main.cpp -o client

clean:
	rm -f server client
