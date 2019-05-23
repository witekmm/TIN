#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>

#include "../Pipes/NetworkConnections.h"
#include "ServerOperations.h"
#include "NetLibs.h"

class Network: public ServerOperation{
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
  int sockets;

  Connections clientPipe;
public:
  Network(int maxConnections, int port, string ip);
  void receiveBuffer(int socketNumber);
  void sendBuffer(int socketNumber);
  void waitForSignal();

  void clearLists();
  void addSocket(int socketNumber);
  void closeSocket(int socketNumber);
  void closeServer();
  void clearSocket(int socketNumber);
  void updateFdmax();
};

#endif
