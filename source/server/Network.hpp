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

using namespace std;

class Network{
    int serverSocket;

    Handling &handling;
    Server &server;

public:
    //konstruktor
    Network(int socketNumber, Server& serv){
        serverSocket = socketNumber;
        server = serv;
    }

    void setHandling( Handling &hand){
        handling = hand;
    }

    //Połącz z klientem
    int connectClient(fd_set &socketList , int fdmax){
        struct sockaddr_in client = { };
        socklen_t addrlen = sizeof( client );
        //połaczenie nieblokujące
        int newfd = accept4(serverSocket, (struct sockaddr*)&client, &addrlen , SOCK_NONBLOCK);
        //Brak połączenia
        if( newfd == -1){
            handling.cannotConnect();
            return fdmax;
        }
        //Połączono
        else{
            FD_SET( newfd , socketList);
            handling.connectionCreated(newfd);
            return (newfd > fdmax) ? newfd : fdmax;
        }
    }

    void readMessage(int socketNumber){
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

    char* readNext(int socketNumber){
        char *msg;
        int messageLen = recv(socketNumber , msg , MAX_MSG_SIZE , 0);
        if(messageLen <= 0 ) return NULL;
        else return msg;
    }

    void exceptionSignal(int socketNumber){
        disconnectClient(socketNumber);
    }

    int sendBack(char* message,int messageLen, int socketNumber){
        int sendLen = send(socketNumber , message , messageLen, 0);
        if(sendLen == -1){
            return -1;
        }
        else{
            return 0;
        }
    }

    int disconnectClient(int socketNumber){
      int error = closeSocket(socketNumber);
      if(error == -2){
          handling.cannotCloseServer();
      }
      else if(error == -1){
          handling.incorrectSocket(socketNumber);
      }
      else if(!error){
          handling.socketIsClosed(socketNumber);
      }
    }

    int getServerSocket(){
        return serverSocket;
    }

    int getFdMax(){
        return server.getFdMax();
    }

    int checkIfSocket(int socketNumber){
        return server.checkIfSocket(socketNumber);
    }

    void closeServerSocket(){
        server.closeServerSocket();
        server.stopServer();
    }

}
