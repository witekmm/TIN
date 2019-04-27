#include "NetLibs.h"
#include "Network.h"

Network::Network(){
  sockets==0;
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_ZERO(&this->master);
  int fdmax==0;
}

int Network::startServer(int maxConnections, int port){
  Server temp(maxConnections, port);
  this->server=temp;
  if(this->server.createServerSocket() == -1) return -1;
  if(this->server.bindServerSocket() == -1) return -1;
  if(this->server.listenServerSocket() == -1) return -1;
  addSocket(server.getSocketNumber());
  return 0;
}

void Network::clearSocket(int socketNumber){
  int i=0;
  for(i ; i < this->sockets;i++){
    if(socketNumber == this->activeSockets[i]) break;
  }
  this->activeSockets.erase(i);
  for(i = 0 ; i<this->sockets-1 ; i++){
    if(socketNumber == this->activeClients[i].getSocketNumber()) break;
  }
  this->activeSockets.erase(i);
  this->sockets--;
  FD_CLR(socketNumber , &master);
}

void Network::addSocket(int socketNumber){
  FD_SET(socketNumber , &master);
  this->activeSockets.push_back(socketNumber);
  this->sockets++;
  updateFdmax();
}

void Network::updateFdmax(){
  int max=0;
  for(int i = 0;int<this->sockets;i++){
    if(this->activeSockets[i]>max) max = this->activeSockets[i];
  }
  this->fdmax=max;
}

int Network::checkIfSocket(int socketNumber){
  for(int i = 0;i<this->sockets;i++){
    if(socketNumber==this->activeSockets[i]) return 0;
  }
  return 1;
}

void Network::clearLists(){
  /*FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_COPY(&this->master,&this->readfds);
  FD_COPY(&this->master,&this->writefds);
  FD_COPY(&this->master,&this->exceptionfds);*/
  this->readfds=this->master;
  this->writefds=this->master;
  this->exceptionfds->this->master;
}

void Network::closeSocket(int socketNumber){
  shutdown(socketNumber, SHUT_RDWR);
  close(socketNumber);
  clearSocket(socketNumber);
  updateFdmax();
}

void Network::selectDescriptor(){
  clearLists();
  if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, NULL) == -1){
    perror("Cannot select descriptor");
    return;
  }
  else{
    for(int socketNumber=0;socketNumber<this->sockets;socketNumber++){
      if(FD_ISSET(socketNumber , &this->readfds)){
        //NOWE POŁĄCZENIE
        if(socketNumber == serverSocket) connectClient();
        else //ODBIÓR WIADOMOSCI
      }
      if(FD_ISSET(socketNumber , &this->writefds)){
        pisz;
      }
      if(FD_ISSET(socketNumber , &this->exceptionfds)){
        sygnał;
      }
    }
  }
}

void connectClient(){
  fdnumber = this->server.acceptConnection();
  if(fdnumber==-1) return;
  Client NewClient(fdnumber);
  addSocket(fdnumber);
  this->activeClients.push_back(NewClient);
}
