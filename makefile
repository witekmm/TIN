SV = Server/
NT = $(SV)Network/
CT = $(SV)Controller/
LG = $(SV)Logic/
CS = $(SV)ClientSession/
DB = $(SV)Database/
MSG = Messages/
NET = $(NT)NetLibs.h
OBJS = main.o CLI.o MainConstants.o Network.o ServerOperations.o Message.pb.o
PIPES = ClientSessionPipes.o
LOGIC = MessageHandler.o DataBaseConnector.o Database.o
CC = g++
<<<<<<< HEAD
=======

>>>>>>> 6b6554a558efc62dcefe53b29f498f1406b36c71
FLAGS = -std=c++11 -pthread -I/usr/local/include
LINKER_FLAGS = -L/usr/local/lib -lprotobuf -pthread

all: server

server: $(OBJS)
	$(CC) $(OBJS) -o server1 $(FLAGS) $(LINKER_FLAGS)

DataBaseConnector.o: $(LG)DataBaseConnector.cpp $(LG)DataBaseConnector.h
	$(CC) -c $(LG)DataBaseConnector.cpp

Database.o: $(DB)Database.cpp $(DB)Database.h
	$(CC) -c $(DB)Database.cpp

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
