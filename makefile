all: server client

server:	main.cpp
	g++ main.cpp -o server

client: client.cpp
	g++ client.cpp -o client

clean:
	rm -f server client
