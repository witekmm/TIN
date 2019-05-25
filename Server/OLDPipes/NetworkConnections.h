#ifndef NETWORK_CONNECTIONS_H
#define NETWORK_CONNECTIONS_H

#include "NetworkPipe.h"

#include <memory>
#include <map>
#include <pthread.h>

class Connections{
  //std::vector < std::pair < std::shared_ptr < NetworkPipe > , int > > pipes;
  std::map< int , std::shared_ptr<NetworkPipe> > pipes;

public:
  Connections();
  void insertPipe(std::shared_ptr<NetworkPipe> pipe, int fd);
  void deletePipe(int fd);

  std::shared_ptr<NetworkPipe> getPipe(int fd);
};

#endif
