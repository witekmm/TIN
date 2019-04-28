NT = Network/
CT = Controller/
TT = Transport/
all: server

server: main.cpp $(CT)MainConstants.cpp $(NT)Server.cpp $(NT)Network.cpp $(NT)Client.cpp $(TT)Transport.cpp
	g++ -pthread main.cpp $(CT)MainConstants.cpp $(NT)Server.cpp $(NT)Network.cpp $(NT)Client.cpp $(TT)Transport.cpp -o server

clean:
	rm -f server
