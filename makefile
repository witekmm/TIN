all: server client

server:	main.cpp
	g++ -pthread main.cpp -o server

client: client.cpp
	g++ -pthread client.cpp -o client

clean:
	rm -f server client
