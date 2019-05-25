SV = Server/
NT = $(SV)Network/
CT = $(SV)Controller/
LG = $(SV)Logic/
CS = $(SV)ClientSession/
MSG = Messages/
NET = $(NT)NetLibs.h
OBJS = main.o CLI.o MainConstants.o Network.o ServerOperations.o Message.pb.o
PIPES = ClientSessionPipes.o
LOGIC = MessageHandler.o
CC = g++
FLAGS = -lpthread -pthread -lprotobuf -std=c++11

all: server

server: $(OBJS) $(LOGIC)
	$(CC) $(OBJS) $(LOGIC) -o server $(FLAGS)

MessageHandler.o: $(LG)MessageHandler.cpp $(LG)MessageHandler.h
	$(CC) -c $(LG)MessageHandler.cpp

MainConstants.o: $(CT)MainConstants.h $(CT)MainConstants.cpp
	$(CC) -c $(CT)MainConstants.cpp

Network.o: $(NET) $(NT)Network.h $(NT)Network.cpp $(NT)ServerOperations.h
	$(CC) -c $(NT)Network.cpp

CLI.o: $(CT)CLI.h	$(CT)CLI.cpp $(NT)Network.h $(NT)ServerOperations.h
	$(CC) -c $(CT)CLI.cpp

ServerOperations.o: $(NET) $(NT)ServerOperations.h $(NT)ServerOperations.cpp
	$(CC) -c $(NT)ServerOperations.cpp

ClientSessionPipes.o: $(CS)ClientSessionPipes.cpp $(CS)ClientSessionPipes.h
	$(CC) -c $(CS)ClientSessionPipes.cpp

main.o: $(SV)main.cpp
	$(CC) -c $(SV)main.cpp

Message.pb.o: $(MSG)Message.pb.cc $(MSG)Message.pb.h
	$(CC) -c  $(MSG)Message.pb.cc

clean:
	rm -f *.o server
