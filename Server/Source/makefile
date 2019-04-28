NT = Network/
CT = Controller/
all: server

server: main.cpp $(CT)MainConstants.cpp $(NT)Server.cpp $(NT)Network.cpp $(NT)Client.cpp
	g++ -pthread main.cpp $(CT)MainConstants.cpp $(NT)Server.cpp $(NT)Network.cpp $(NT)Client.cpp -o server

clean:
	rm -f server
