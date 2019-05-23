SV = Server/
NT = $(SV)Network/
CT = $(SV)Controller/
LG = $(SV)Logic/
TT = $(SV)Transport/
PP = $(SV)Pipes/
CL = $(SV)Client/
MSG = Messages/
NET = $(NT)NetLibs.h
OBJS = main.o ServerConnections.o NetworkPipe.o LogicPipe.o NetworkConnections.o MainConstants.o Network.o Message.pb.o
CC = g++
FLAGS = -lpthread -pthread -lprotobuf -std=c++11

all: server

server: $(OBJS)
	$(CC) $(OBJS) -o server $(FLAGS)

NetworkPipe.o: $(PP)NetworkPipe.h $(PP)NetworkPipe.cpp
	$(CC) -c $(PP)NetworkPipe.cpp

ServerConnections.o: $(PP)ServerConnections.cpp $(PP)ServerConnections.h $(PP)ClientStatus.h
	$(CC) -c $(PP)ServerConnections.cpp

LogicPipe.o: $(PP)LogicPipe.h $(PP)LogicPipe.cpp
	$(CC) -c $(PP)LogicPipe.cpp

NetworkConnections.o: $(PP)NetworkConnections.h $(PP)NetworkConnections.cpp
	$(CC) -c $(PP)NetworkConnections.cpp

MainConstants.o: $(CT)MainConstants.h $(CT)MainConstants.cpp
	$(CC) -c $(CT)MainConstants.cpp

Network.o: $(NET) $(NT)Network.h $(NT)Network.cpp $(NT)ServerOperations.h $(NT)ServerOperations.cpp
	$(CC) -c $(NT)Network.cpp $(NT)ServerOperations.cpp

main.o: $(SV)main.cpp
	$(CC) -c $(SV)main.cpp

Message.pb.o: $(MSG)Message.pb.cc $(MSG)Message.pb.h
	$(CC) -c  $(MSG)Message.pb.cc

clean:
	rm -f *.o server
