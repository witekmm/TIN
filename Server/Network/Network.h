#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>

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
  std::vector<int> activeSockets;

public:
  Network(int maxConnections, int port, std::string ip);
  void receiveBuffer(int socketNumber);
  void sendBuffer(int socketNumber);
  void waitForSignal();

  void prepareLists();
  void addSocket(int socketNumber);
  int closeSocket(int socketNumber);
  int closeSocketWithBlocking(int socketNumber);
  void clearSocket(int socketNumber);
  void updateFdmax();
  bool checkIfSocket(int socketNumber);

  int startServer();
  void stopWaiting();
  void closeServer();

  bool isServerWaiting();
};

#endif
