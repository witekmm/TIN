#include "Network.h"

int Network::createServerSocket(){
  int yes = 1;
  this->serverSocket=socket(AF_INET, SOCK_STREAM, 0);
  if(this->serverSocket < 0) return 1;
  if(setsockopt( this->serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == - 1 ) return 1;
  FD_SET(this->serverSocket,&master);
  activeSockets.push_back(this->serverSocket);
  this->sockets+=1;
  return 0;
}

int Network::bindServerSocket(){
  if( bind(this->serverSocket, (struct sockaddr*) &(this->server), this->len) < 0) {
    shutdown(this->serverSocket, SHUT_RDWR);
    close(this->serverSocket);
    clearSocket(this->serverSocket);
    return 1;
  }
  else return 0;
}

int Network::listenServerSocket(){
  if(listen(this->serverSocket, this->maxConnections ) < 0 ){
    shutdown(this->serverSocket, SHUT_RDWR);
    close(this->serverSocket);
    clearSocket(this->serverSocket);
    return 1;
  }
  else return 0;
}

void Network::clearSocket(int socketNumber){
  int i=0;
  for(i;i>socket;i++){
    if(socketNumber == activeSockets[i]) break;
  }
  this->activeSockets.erase(i);
  this->sockets-=1;
}

void Network::updateFdmax(){

}
