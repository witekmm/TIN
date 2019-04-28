#include "NetLibs.h"
using namespace std;

#ifndef NETWORK_H
#define NETWORK_H

#include "Server.h"
#include "Client.h"

#include <vector>

class Network{
  Server server;
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
  //quite obvious
  int startServer(int maxConnections, int port, string ip);
  void addSocket(int socketNumber);
  //signal from sockets
  void selectDescriptor();
  //Close choosen socket
  void closeSocket(int socketNumber);
  //Find new fdmax after closing socket with biggest number
  void updateFdmax();
  //Clears choosen socket from activeSockets and decreases sockets
  void clearSocket(int socketNumber);
  //return 0 if socket , 1 if not
  int checkIfSocket(int socketNumber);
  //Clears waiting lists
  void clearLists();
  //KLIENT
  void connectClient();
};

#endif
