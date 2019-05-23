#ifndef SERVER_OPERATION_H
#define SERVER_OPERATION_H

#include "NetLibs.h"
#include <iostream>

class ServerOperation{
  int port;
  std::string serverIP;
  int maxConnections;
  int socketNumber;
  sockaddr_in serverAddress{};
  socklen_t len;
public:
  ServerOperation(int maxConnections, int port, std::string ip);
  int createServerSocket();
  int bindServerSocket();
  int listenServerSocket();
  int acceptConnection();
  int getSocketNumber();
};

#endif
