#include "NetLibs.h"

#ifndef SERVER_H
#define SERVER_H

class Server{
  int socketNumber;
  //transport address and port
  sockaddr_in serverAddress{};
  socklen_t len;
  //max connections pending on for accept
  int maxConnections;
public:
  Server(int maxConnections);
  //create socket for server
  int createServerSocket();
  //bind server address to socket
  int bindServerSocket();
  //Server in passive mode
  int listenServerSocket();
  //0 if accept gone well, 1 if not
  int acceptConnection();
};

#endif
