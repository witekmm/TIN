#include "ServerOperations.h"

ServerOperation::ServerOperation(int maxConnections, int port, string ip): maxConnections(maxConnections), port(port), ip(ip){
  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_port = htons(port);
  this->len = sizeof(this->serverAddress);
}

int ServerOperation::createServerSocket(){
  if( inet_pton(AF_INET, (char*)&this->serverIP, &this->serverAddress.sin_addr) <= 0){
    return -1;
  }
  int yes = 1;
  this->socketNumber = socket(AF_INET, SOCK_STREAM, 0);
  if(this->socketNumber < 0) return -1;
  if(setsockopt(this->socketNumber, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == - 1){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  return this->socketNumber;
}

int ServerOperation::bindServerSocket(){
  if( bind(this->socketNumber, (struct sockaddr*)&(this->serverAddress), this->len) < 0){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  else return 0;
}

int ServerOperation::listenServerSocket(){
  if(listen(this->socketNumber, this->maxConnections) < 0){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  else return 0;
}

int ServerOperation::acceptConnection(){
  struct sockaddr_in client = {};
  socklen_t addrlen = sizeof( client );
  //połaczenie nieblokujące
  int newfd = accept4(this->socketNumber, (struct sockaddr*)&client, &addrlen, SOCK_NONBLOCK);
  //Brak połączenia
  if(newfd == -1) return -1;
  //Połączono
  else return newfd;
}

int ServerOperation::getSocketNumber(){
  return this->socketNumber;
}
