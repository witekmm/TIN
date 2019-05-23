#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>

#include "../Pipes/NetworkConnections.h"
#include "ServerOperation.h"

class Network: public ServerOperation{
  bool wotking;
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

  Connection clientPipe;
public:
  Network(int maxConnections, int port, string ip);
  void connectClient();
  void receiveBuffer(int socketNumber);
  void sendBuffer(int socketNumber);
  void clearLists();
  void waitForSignal();

  void addSocket(int socketNumber);
  void closeSocket(int socketNumber);
  void closeServer();
};

#endif
