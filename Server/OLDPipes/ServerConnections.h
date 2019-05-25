#ifndef SERVER_CONNECTIONS_H
#define SERVER_CONNECTIONS_H

#include "LogicPipe.h"
#include "ClientStatus.h"

#include <memory>
//#include <vector>
//#include <utility>
#include <map>
#include <pthread.h>

struct userData{
  ClientStatus status;
  std::string& login;
};

class ServerConnections{
  //std::vector < std::pair < std::shared_ptr < LogicPipe > , ClientStatus > > pipes;
  std::map< ClientStatus , < std::shared_ptr<LogicPipe> > pipes;
};

#endif
