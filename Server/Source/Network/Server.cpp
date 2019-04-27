#include "NetLibs.h"
#include "Server.h"

Server::Server(int maxConnections){
  this->len = sizeof(this->server);
  this->maxConnections=maxConnections;
}

int Server::createServerSocket(){
  int yes = 1;
  this->socketNumber=socket(AF_INET, SOCK_STREAM, 0);
  if(this->socketNumber < 0) return -1;
  if(setsockopt( this->socketNumber, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == - 1 ){
    shutdown(this->socketNumber , RDWR);
    close(this->socketNumber);
    return -1;
  }
  return this->socketNumber;
}

int Server::bindServerSocket(){
  if( bind(this->socketNumber, (struct sockaddr*) &(this->server), this->len) < 0) {
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return 1;
  }
  else return 0;
}


int Network::listenServerSocket(){
  if(listen(this->socketNumber, this->maxConnections ) < 0 ){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    clearSocket(this->socketNumber);
    return 1;
  }
  else return 0;
}
