#include "NetLibs.h"
#include "Server.h"
using namespace std;

Server::Server(){
  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_port = htons(DEFAULT_SERVER_PORT);
  this->len = sizeof(this->serverAddress);
  this->maxConnections=DEFAULT_MAX_CONNECTIONS;
  this->port=DEFAULT_SERVER_PORT;
  this->serverIP=string(DEFAULT_SERVER_IP);
}

Server::Server(int maxConnections, int port, string ip){
  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_port = htons(port);
  this->len = sizeof(this->serverAddress);
  this->maxConnections=maxConnections;
  this->port=port;
  this->serverIP=ip;
}

int Server::createServerSocket(){
  if( inet_pton( AF_INET, (char*)&this->serverIP, &this->serverAddress.sin_addr ) <= 0 ){
    return -1;
  }
  int yes = 1;
  this->socketNumber=socket(AF_INET, SOCK_STREAM, 0);
  if(this->socketNumber < 0) return -1;
  if(setsockopt( this->socketNumber, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == - 1 ){
    shutdown(this->socketNumber , SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  return this->socketNumber;
}

int Server::bindServerSocket(){
  if( bind(this->socketNumber, (struct sockaddr*) &(this->serverAddress), this->len) < 0) {
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  else return 0;
}


int Server::listenServerSocket(){
  if(listen(this->socketNumber, this->maxConnections ) < 0 ){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  else return 0;
}

int Server::acceptConnection(){
  struct sockaddr_in client = {};
  socklen_t addrlen = sizeof( client );
  //połaczenie nieblokujące
  int newfd = accept4(this->socketNumber, (struct sockaddr*)&client, &addrlen , SOCK_NONBLOCK);
  //Brak połączenia
  if(newfd == -1) return -1;
  //Połączono
  else return newfd;
}

int Server::getSocketNumber(){
  return this->socketNumber;
}
