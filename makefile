SV = Server/
NT = $(SV)Network/
CT = $(SV)Controller/
LG = $(SV)Logic/
TT = $(SV)Transport/
MSG = Messages/
NET = $(NT)NetLibs.h
OBJS = main.o MainConstants.o Client.o Network.o Server.o Transport.o Message.pb.o
CC = g++
FLAGS = -lpthread -pthread -lprotobuf -std=c++11

all: server

server: $(OBJS)
	$(CC) $(OBJS) -o server $(FLAGS)

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

clean:
	rm -f *.o server
