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
    pthread_mutex_lock(&this->mutex);
    prepareLists();
    if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, &this->tv) < 1){
      break;
    }
    else{
      for(auto it=this->activeSockets.begin() ; it!=this->activeSockets.end() ; it++){
        int tmp = *it;
        if(FD_ISSET(tmp , &this->readfds)){
          if(tmp == ServerOperation::getSocketNumber()){
            int newfd = ServerOperation::acceptConnection();
            if(newfd > 0){
              addSocket(newfd);
              break;
            }
            else{
              puts("cannot connect");
            }
          }
          else{
            receiveBuffer(tmp);
            puts("0.0");
          }
        }
        puts("1");
        if(FD_ISSET(tmp , &this->writefds)){
          puts("1.1");
          sendBuffer(tmp);
        }
        puts("2");
        if(FD_ISSET(tmp , &this->exceptionfds)){
          puts("2.2");
          closeSocket(tmp);
        }
      }
    }
    pthread_mutex_unlock(&this->mutex);
  }
}

void Network::prepareLists(){
  /*
  this->readfds=this->master;
  this->writefds=this->master;
  this->exceptionfds=this->master;*/
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  for(auto it = this->activeSockets.begin() ; it != this->activeSockets.end() ; it++){
    FD_SET(*it , &this->readfds);
    FD_SET(*it , &this->writefds);
    FD_SET(*it , &this->exceptionfds);
  }
}

void Network::receiveBuffer(int socketNumber){

}

void Network::sendBuffer(int socketNumber){

}

void Network::addSocket(int socketNumber){
  FD_SET(socketNumber , &this->master);
  this->activeSockets.push_back(socketNumber);
  updateFdmax();
}

void Network::closeSocket(int socketNumber){
  shutdown(socketNumber, SHUT_RDWR);
  close(socketNumber);
  clearSocket(socketNumber);
  updateFdmax();
}

void Network::closeServer(){
  for(auto it = this->activeSockets.begin() ; it != this->activeSockets.end() ; it++){
    if(*it != ServerOperation::getSocketNumber()){
      shutdown(*it, SHUT_RDWR);
      close(*it);
      clearSocket(*it);
    }
  }
  shutdown(ServerOperation::getSocketNumber(), SHUT_RDWR);
  close(ServerOperation::getSocketNumber());
  this->working=false;
}

void Network::clearSocket(int socketNumber){
  for(auto it = this->activeSockets.begin() ; it != this->activeSockets.end(); it++){
    if(*it == socketNumber){
      this->activeSockets.erase(it);
      break;
    }
  }
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
  int fdnew=ServerOperation::createServerSocket();
  if(fdnew == -1) return -1;
  addSocket(fdnew);
  if(ServerOperation::bindServerSocket() == -1) return -1;
  if(ServerOperation::listenServerSocket() == -1) return -1;
  return 0;
}
