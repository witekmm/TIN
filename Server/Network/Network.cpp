#include "Network.h"

Network::Network(int maxConnections, int port, string ip):working(true), ServerOperation(maxConnections,port,ip){
  this->tv.tv_sec = 1;
  this->tv.tv_usec = 0;
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_ZERO(&this->master);
}

void Network::waitForSignal(){
  while(this->working){
    clearLists();
    if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, NULL) < 1){
      break;
    }
    else{
      for(int i=0 ; i<this->sockets ; i++){
        if(FD_ISSET(this->activeSockets[i] , &this->readfds)){
          if(this->activeSockets[i] == ServerOperation::getSocketNumber()){
            int newfd = ServerOperation::acceptConnection();
            if(newfd > 0){
              addSocket(newfd);
            }
            else{
              puts("cannot connect");
            }
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

void Network::receiveBuffer(int socketNumber){

}

void Network::sendBuffer(int socketNumber){

}

void Network::addSocket(int socketNumber){
  FD_SET(socketNumber , &master);
  this->activeSockets.push_back(socketNumber);
  this->sockets++;
  updateFdmax();
}

void Network::closeSocket(int socketNumber){
  shutdown(socketNumber, SHUT_RDWR);
  close(socketNumber);
  clearSocket(socketNumber);
  updateFdmax();
}

void Network::closeServer(){
  for(int i = 0; i < sockets ; i++){
    if(this->activeSockets[i] != ServerOperation::getSocketNumber()){
      shutdown(this->activeSockets[i], SHUT_RDWR);
      close(this->activeSockets[i]);
      clearSocket(this->activeSockets[i]);
    }
  }
  shutdown(ServerOperation::getSocketNumber(), SHUT_RDWR);
  close(ServerOperation::getSocketNumber());
  this->working=false;
}

void Network::clearSocket(int socketNumber){
  for(vector<int>::iterator it = this->activeSockets.begin() ; it != this->activeSockets.end(); it++){
    if(*it == socketNumber){
      this->activeSockets.erase(it);
      break;
    }
  }
  this->sockets--;
  FD_CLR(socketNumber , &this->master);
}

void Network::updateFdmax(){
  int max=0;
  for(auto it = this->activeSockets.begin() ; it != this->activeSockets.end() ; it++){
    if(*it > max) max = *it;
  }
  this->fdmax=max;
}

int Network::startServer(){
  int fdnew=createServerSocket();
  if(fdnew == -1) return -1;
  addSocket(fdnew);
  if(bindServerSocket() == -1) return -1;
  if(listenServerSocket() == -1) return -1;
  return 0;
}
