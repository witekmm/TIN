#ifndef SERVER_OPERATION_H
#define SERVER_OPERATION_H

#include "NetLibs.h"
#include <iostream>
#include <cstring>

class ServerOperation{
  int port;
  std::string serverIP;
  int maxConnections;
  int socketNumber;
  sockaddr_in serverAddress{};
  socklen_t len;
  bool isSocketNumberSet;
  bool isSocketListening;
public:
  ServerOperation(int maxConnections, int port, std::string ip);
  int createServerSocket();
  int bindServerSocket();
  int listenServerSocket();
  int acceptConnection();
  int getSocketNumber();

  void closeServer();
  bool getIsSocketNumberSet();
  bool getIsSocketListening();
  void setPort(int port);
};

#endif
