#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

#define MAX_MSG_SIZE 256

#include "Handling.hpp"
#include "Server.hpp"
#include "../message.cpp"

class Network{
    int serverSocket;
    Handling &handling;
    Server &server

public:
    //konstruktor
    Network(int socketNumber){
        serverSocket = socketNumber;
    }

    void setHandling( Handling &hand){
        handling = hand;
    }

    void setServer(Server &serv){
        server = serv;
    }

    //Połącz z klientem
    int connectClient(fd_set &socketList , int fdmax){
        struct sockaddr_in client = { };
        socklen_t addrlen = sizeof( client );
        //połaczenie nieblokujące
        int newfd = accept4(serverSocket, (struct sockaddr*)&client, &addrlen) , SOCK_NONBLOCK);
        //Brak połączenia
        if( newfd == -1){
            handling.cannotConnect();
            return fdmax;
        }
        //Połączono
        else{
            FD_SET( newfd , socketList);
            handling.connectionCreated(newfd);
            return (newfd > fdmax) newfd : fdmax;
        }

    }

    void readHeader(int socketNumber){
        char message[MAX_MSG_SIZE];
        int messageLen = recv(socketNumber , &message , MAX_MSG_SIZE , 0);
        if(messageLen == -1){
            handling.cannotReceive(socketNumber);
            return;
        }
        else{
            handling.handleMessage(message , messageLen , socketNumber);
            return;
        }
    }

    int sendBack(char* message,int messageLen, int socketNumber){
        int sendLen = send(socketNumber, messageLen, 0);
        if(sendLen == -1){
            return -1;
        }
        else{
            return 0;
        }
    }

    int disconnectClient(int socketNumber){
        return closeSocket(socketNumber);
    }

}
