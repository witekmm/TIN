SV = Server/
NT = $(SV)Network/
CT = $(SV)Controller/
LG = $(SV)Logic/
TT = $(SV)Transport/
PP = $(SV)Pipes/
CL = $(SV)Client/
MSG = Messages/
NET = $(NT)NetLibs.h
OBJS = main.o NetworkPipe.o LogicPipe.o NetworkConnections.o MainConstants.o Client.o Network.o Server.o Message.pb.o
CC = g++
FLAGS = -lpthread -pthread -lprotobuf -std=c++11

all: server

server: $(OBJS)
	$(CC) $(OBJS) -o server $(FLAGS)

NetworkPipe.o: $(PP)NetworkPipe.h $(PP)NetworkPipe.cpp
	$(CC) -c $(PP)NetworkPipe.cpp

LogicPipe.o: $(PP)LogicPipe.h $(PP)LogicPipe.cpp
	$(CC) -c $(PP)LogicPipe.cpp

NetworkConnections.o: $(PP)NetworkConnections.h $(PP)NetworkConnections.cpp
	$(CC) -c $(PP)NetworkConnections.cpp

Server.o: $(NET) $(NT)Server.h $(NT)Server.cpp
	$(CC) -c $(NT)Server.cpp

MainConstants.o: $(CT)MainConstants.h $(CT)MainConstants.cpp
	$(CC) -c $(CT)MainConstants.cpp

Client.o: $(NET) $(NT)Client.h $(NT)Client.cpp
	$(CC) -c $(NT)Client.cpp

Network.o: $(NET) $(NT)Network.h $(NT)Network.cpp
	$(CC) -c $(NT)Network.cpp

Transport.o: $(TT)Transport.cpp $(TT)Transport.h $(NT)Network.h
	$(CC) -c $(TT)Transport.cpp

main.o: $(SV)main.cpp
	$(CC) -c $(SV)main.cpp

Message.pb.o: $(MSG)Message.pb.cc $(MSG)Message.pb.h
	$(CC) -c  $(MSG)Message.pb.cc

HandleMessage.o: $(LG)HandleMessage.cpp $(LG)HandleMessage.h
	$(CC) -c $(LG)HandleMessage.cpp

HandleDataBase.o: $(LG)HandleDataBase.cpp $(LG)HandleDataBase.h
	$(CC) -c $(LG)HandleDataBa
	se.cpp

CreateReply.o: $(LG)CreateReply.cpp $(LG)CreateReply.h
	$(CC) -c $(LG)CreateReply.cpp

Interface.o: $(TT)Interface.cpp $(TT)Interface.h
	$(CC) -c $(TT)Interface.cpp

clean:
	rm -f *.o server
