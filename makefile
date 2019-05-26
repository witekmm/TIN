SV = Server/
NT = $(SV)Network/
CT = $(SV)Controller/
LG = $(SV)Logic/
CS = $(SV)ClientSession/
DB = $(SV)Database/
MSG = Messages/
NET = $(NT)NetLibs.h
OBJS = main.o CLI.o MainConstants.o Network.o ServerOperations.o Message.pb.o
PIPES = ClientSessionPipes.o ClientSessionPipe.o Client.o BytesMessage.o
LOGIC = MessageHandler.o DataBaseConnector.o Database.o RepliesCreator.o
CC = g++
FLAGS = -std=c++11 -pthread -I/usr/local/include
LINKER_FLAGS = -L/usr/local/lib -lprotobuf
DB_FLAGS = -L/usr/lib -lmysqlcppconn

all: server

server: $(OBJS) $(PIPES) $(LOGIC)
	$(CC) $(OBJS) $(PIPES) $(LOGIC) -o server1 $(FLAGS) $(LINKER_FLAGS) $(DB_FLAGS)

DataBaseConnector.o: $(LG)DataBaseConnector.cpp $(LG)DataBaseConnector.h
	$(CC) -c $(LG)DataBaseConnector.cpp

MessageHandler.o: $(LG)MessageHandler.cpp $(LG)MessageHandler.h
	$(CC) -c $(LG)MessageHandler.cpp

RepliesCreator.o: $(LG)RepliesCreator.cpp $(LG)RepliesCreator.h
	$(CC) -c $(LG)RepliesCreator.cpp

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

ClientSessionPipes.o: $(NET) $(CS)ClientSessionPipes.cpp $(CS)ClientSessionPipes.h
	$(CC) -c $(CS)ClientSessionPipes.cpp

ClientSessionPipe.o: $(NET) $(CS)ClientSessionPipe.cpp $(CS)ClientSessionPipe.h
	$(CC) -c $(CS)ClientSessionPipe.cpp

Client.o: $(CS)Client.cpp $(CS)Client.h
	$(CC) -c $(CS)Client.cpp

BytesMessage.o: $(CS)BytesMessage.cpp $(CS)BytesMessage.h
	$(CC) -c $(CS)BytesMessage.cpp

main.o: $(SV)main.cpp
	$(CC) -c $(SV)main.cpp

Message.pb.o: $(MSG)Message.pb.cc $(MSG)Message.pb.h
	$(CC) -c  $(MSG)Message.pb.cc

clean:
	rm -f *.o server
