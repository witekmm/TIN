#include "Network.h"

Network::Network(int maxConnections, int port, std::string ip, std::shared_ptr<ClientSessionPipes> clients):clients(clients) , working(false), ServerOperation(maxConnections,port,ip){
  this->tv.tv_sec = 1;
  this->tv.tv_usec = 0;
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_ZERO(&this->master);
}

void Network::waitForSignal(){
  perror("Server is waiting for signal from sockets");
  pthread_mutex_lock(&this->mutex);
  this->working=true;
  pthread_mutex_unlock(&this->mutex);
  while(this->working){
    pthread_mutex_lock(&this->mutex);
    puts("MUT");
    prepareLists();
    if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, 0) < 1){
      break;
    }
    else{
      for(auto it=this->activeSockets.begin() ; it!=this->activeSockets.end() ; it++){
        int tmp = *it;
        if(FD_ISSET(tmp , &this->readfds)){
          if(tmp == ServerOperation::getSocketNumber()){
            int newfd = ServerOperation::acceptConnection();
            if(newfd > 0){
              puts("NEW CLIENT CONNECTED");
              addSocket(newfd);
              this->clients->createClientSession(newfd);
              break;
            }
            else{
              puts("cannot connect");
            }
          }
          else{
            if(this->clients->readBytes(tmp) == -1){
                closeSocket(tmp);
                this->clients->deleteClientSession(tmp);
                break;
            }
          }
        }
        if(FD_ISSET(tmp , &this->writefds)){
          if(this->clients->writeBytes(tmp) == -1){
              closeSocket(tmp);
              this->clients->deleteClientSession(tmp);
              break;
          }
        }
        if(FD_ISSET(tmp , &this->exceptionfds)){
          closeSocket(tmp);
          this->clients->deleteClientSession(tmp);
          break;
        }
      }
    }
    pthread_mutex_unlock(&this->mutex);
  }
}

void Network::prepareLists(){
  this->readfds=this->master;
  this->writefds=this->master;
  this->exceptionfds = this->master;
  /*FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  for(auto it = this->activeSockets.begin() ; it != this->activeSockets.end() ; it++){
    FD_SET(*it , &this->readfds);
    FD_SET(*it , &this->writefds);
    FD_SET(*it , &this->exceptionfds);
  }*/
}

void Network::addSocket(int socketNumber){
  FD_SET(socketNumber , &this->master);
  this->activeSockets.push_back(socketNumber);
  updateFdmax();
}

int Network::closeSocket(int socketNumber){
  if(socketNumber==ServerOperation::getSocketNumber()) return 1;
  if(!checkIfSocket(socketNumber)) return 2;
  shutdown(socketNumber, SHUT_RDWR);
  close(socketNumber);
  clearSocket(socketNumber);
  updateFdmax();
  return 0;
}

int Network::closeSocketWithBlocking(int socketNumber){
  pthread_mutex_lock(&this->mutex);
  int result = closeSocket(socketNumber);
  pthread_mutex_unlock(&this->mutex);
  return 0;
}

void Network::closeServer(){
  pthread_mutex_lock(&this->mutex);
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
  pthread_mutex_unlock(&this->mutex);
  ServerOperation::closeServer();
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
  if(ServerOperation::bindServerSocket() == -1) return -1;
  addSocket(fdnew);
  return 0;
}

void Network::stopWaiting(){
  pthread_mutex_lock(&this->mutex);
  this->working=false;
  pthread_mutex_unlock(&this->mutex);
}

bool Network::isServerWaiting(){
  puts("X");
  pthread_mutex_lock(&this->mutex);
  puts("D");
  bool temp = this->working;
  pthread_mutex_unlock(&this->mutex);
  return temp;
}

bool Network::checkIfSocket(int socketNumber){
  for(auto it = this->activeSockets.begin() ; it != this->activeSockets.end() ; it++){
    if(*it > socketNumber) return true;
  }
  return false;
}
