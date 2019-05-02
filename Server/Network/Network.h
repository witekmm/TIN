#include "NetLibs.h"

using namespace std;

#ifndef NETWORK_H
#define NETWORK_H
#include "../Transport/Transport.h"
#include "Server.h"
#include "Client.h"
#include <vector>

class Transport;

class Network{
  //representation of server
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
  //list of sockets that select is listening
  vector<int> activeSockets;
  int sockets;
  //refernece to transport pipe
  Transport& transport;
public:
  Network(Transport& tp);
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
  //this function only pass message to client's buffer
  //client should send as many bytes as he can whenever he can
  int setMessage(string message,int size, string client);
  int setMessage(string message,int size, int socketNumber);
  //send message when network get a signal
  void sendMessage(Client& client);
  //receive message when network get a signal
  void receiveMessage(Client& client);
  //authorize client
  void logInClient(int socketNumber, string login);
  void authorizeClient(int socketNumber, string login);
  //client stuff
  void logOutClient(string login);
  void disconnectClient(string login);
  void disconnectClientBySN(int socketNumber);
  int isClientLogged(int socketNumber);

  Client& findClient(int socketNumber);
};

#endif
