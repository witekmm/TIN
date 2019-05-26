#include "NetworkConnections.h"

Connections::Connections(){}

void Connections::insertPipe(std::shared_ptr<NetworkPipe> pipe, int fd){
  this->pipes.insert({fd,pipe});
}

void Connections::deletePipe(int fd){
  auto search = this->pipes.find(fd);
  if(search!=this->pipes.end()) this->pipes.erase(search);
}

std::shared_ptr<NetworkPipe> Connections::getPipe(int fd){
  auto search = this->pipes.find(fd);
  return search->second;
}
