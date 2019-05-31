#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>

#include "ServerOperations.h"
#include "NetLibs.h"

#include "../ClientSession/ClientSessionPipes.h"

class Network: public ServerOperation{
  pthread_mutex_t mutex;
  bool working;
  struct timeval tv;
  sigset_t _set;
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
  std::shared_ptr<ClientSessionPipes> clients;
public:
  Network(int maxConnections, int port, std::string ip, std::shared_ptr<ClientSessionPipes> clients);
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
