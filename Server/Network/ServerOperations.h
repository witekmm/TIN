#ifndef SERVER_OPERATION_H
#define SERVER_OPERATION_H

#define DEFAULT_SERVER_PORT 50011
#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_MAX_CONNECTIONS 10

#include "NetLibs.h"

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
