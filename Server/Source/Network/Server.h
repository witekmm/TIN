#include "NetLibs.h"

#ifndef SERVER_H
#define SERVER_H

#define DEFAULT_SERVER_PORT 50011
//#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_MAX_CONNECTIONS 10

class Server{
  int socketNumber;
  //transport address and port
  sockaddr_in serverAddress{};
  socklen_t len;
  //max connections pending on for accept
  int maxConnections;
  int port;
public:
  Server();
  Server(int maxConnections, int port);
  //create socket for server
  int createServerSocket();
  //bind server address to socket
  int bindServerSocket();
  //Server in passive mode
  int listenServerSocket();
  //0 if accept gone well, 1 if not
  int acceptConnection();

  int getSocketNumber();
};

#endif
