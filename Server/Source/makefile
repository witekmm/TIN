NT = Network/
CT = Controller/
TT = Transport/
MSG = ../../Messages/
all: server

server: main.cpp $(CT)MainConstants.cpp $(NT)Server.cpp $(NT)Network.cpp $(NT)Client.cpp $(TT)Transport.cpp $(MSG)Message.pb.cc
	g++ -pthread main.cpp $(CT)MainConstants.cpp $(NT)Server.cpp $(NT)Network.cpp $(NT)Client.cpp $(TT)Transport.cpp $(MSG)Message.pb.cc -o server

clean:
	rm -f server
