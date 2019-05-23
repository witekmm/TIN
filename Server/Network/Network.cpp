#include "Network.h"

Network::Network(int maxConnections, int port, string ip):working(true), tv.tv_sec(1), tv.tv_usec(0), ServerOperation(maxConnections,port,ip){
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_ZERO(&this->master);
}

void Network::waitForSignal(){
  while(this->working){
    clearLists();
    if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, &this->tv) < 1){
      return;
    }
    else{
      for(int i=0 ; i<this->sockets ; i++){
        if(FD_ISSET(this->activeSockets[i] , &this->readfds)){
          if(this->activeSockets[i] == ServerOperation::getSocketNumber()){
            if(int newfd = connectClient() > 0) addSocket
          }
          else{
            receiveBuffer(this->activeSockets[i]);
          }
        }
        if(FD_ISSET(this->activeSockets[i] , &this->writefds)){
          sendBuffer(this->activeSockets[i]);
        }
        if(FD_ISSET(this->activeSockets[i] , &this->exceptionfds)){
          closeSocket(this->activeSockets[i]);
        }
      }
    }
  }
}

void Network::clearLists(){
  this->readfds=this->master;
  this->writefds=this->master;
  this->exceptionfds=this->master;
}

void Network::connectClient(){

}
void Network::receiveBuffer(){

}
void Network::sendBuffer(){

}
void addSocket(){

}
void closeSocket(){

}
void closeServer(){

}
