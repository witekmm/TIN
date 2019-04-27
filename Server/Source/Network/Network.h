#include "NetLibs.h"
using namespace std;

#ifndef NETWORK_H
#define NETWORK_H

#include "Server.h"
#include "Client.h"

#include <vector>

class Network{
  //Descriptors list:
  //master - original list
  //readfds - waiting for read action
  //writefds - waiting for write action
  //exceptionfds - waiting for exception signals
  fd_set master, readfds, writefds, exceptionfds;
  //Maximal descriptor number
  int fdmax;
  //list of active sockets
  vector<Client> activeClients;
  vector<int> activeSockets;
  int sockets;
public:
  Network();
  //server configure
  int startServer();
  //signal from sockets
  void selectDescriptor();
  //Close choosen socket
  int closeSocket(int socketNumber);
  //Find new fdmax after closing socket with biggest number
  void updateFdmax();
  //Clears choosen socket from activeSockets and decreases sockets
  void clearSocket(int socketNumber);
  //return 0 if socket , 1 if not
  int checkIfSocket(int socketNumber);
  //Clears waiting lists
  void clearLists();
};

#endif
