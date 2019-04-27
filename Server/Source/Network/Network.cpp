#include "NetLibs.h"
#include "Network.h"

FD_SET(this->serverSocket,&master);
activeSockets.push_back(this->serverSocket);




void Network::clearSocket(int socketNumber){
  int i=0;
  for(i ; i < this->socket;i++){
    if(socketNumber == this->activeSockets[i]) break;
  }
  this->activeSockets.erase(i);
  this->sockets-=1;
}

void Network::addSocket(int socketNumber){
  FD_SET(socketNumber , &master);
  this->activeSockets.push_back(socketNumber);
  this->sockets+=1;
}

void Network::updateFdmax(){
  int max=0;
  for(int i = 0;int<this->sockets;i++){
    max = (this->activeSockets[i]>max) ? this->activeSockets[i] : max;
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

int Network::acceptConnection(){
  struct sockaddr_in client = {};
  socklen_t addrlen = sizeof( client );
  //połaczenie nieblokujące
  int newfd = accept4(this->serverSocket, (struct sockaddr*)&client, &addrlen , SOCK_NONBLOCK);
  //Brak połączenia
  if(newfd == -1) return 1;
  //Połączono
  else{
    addSocket(newfd);
    updateFdmax();
    return 0;
  }
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
        if(socketNumber == serverSocket) //DOŁĄCZENIE NOWEGO ZIOMKA
        //INTERAKCJA Z UŻYTKOWNIKIEM
        else //ODBIÓR WIADOMOSCI
      }
      else if(FD_ISSET(socketNumber , &this->writefds)){
        pisz;
      }
      else if(FD_ISSET(socketNumber , &this->exceptionfds)){
        sygnał;
      }
    }
  }
}
