#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>

#include "../Pipes/NetworkConnections.h"
#include "ServerOperations.h"
#include "NetLibs.h"

class Network: public ServerOperation{
  pthread_mutex_t mutex;
  bool working;
  struct timeval tv;
  //Descriptors list:
  //master - original list
  //readfds - waiting for read action
  //writefds - waiting for write action
  //exceptionfds - waiting for exception signals
  fd_set master, readfds, writefds, exceptionfds;
  //Maximal descriptor number
  int fdmax;
  //list of sockets that select is listening
  vector<int> activeSockets;

  Connections clientPipe;
public:
  Network(int maxConnections, int port, string ip);
  void receiveBuffer(int socketNumber);
  void sendBuffer(int socketNumber);
  void waitForSignal();

  void prepareLists();
  void addSocket(int socketNumber);
  void closeSocket(int socketNumber);
  void closeServer();
  void clearSocket(int socketNumber);
  void updateFdmax();

  int startServer();
};

#endif
