MSG = ../Messages/
CC = g++
FLAGS = -std=c++11 -pthread -I/usr/local/include
LINKER_FLAGS = -L/usr/local/lib -lprotobuf
OBJS = Message.pb.o Client.o

all: client clean.part

client: $(OBJS)
	$(CC) $(OBJS) -o client $(FLAGS) $(LINKER_FLAGS)

Client.o: Client.cpp
	$(CC) -c Client.cpp

Message.pb.o: $(MSG)Message.pb.cc $(MSG)Message.pb.h
	$(CC) -c  $(MSG)Message.pb.cc

clean.part:
	rm -f *.o

clean:
	rm -f *.o client
