#IFNDEF NETWORK_H
#DEFINE NETWORK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class Network{
  fd_set master, readfds, writefds, exceptionfds;
  int activeSockets[];
  sockaddr_in server{};
  socklen_t len;
  int fdmax;
  int serverSocket;
public:
  int createServerSocket();
  int bindServerSocket();
  int listenServerSocket();
  void selectDescriptor();
  int closeSocket(int socketNumber);
  int findNewFdmax(int fdmax);
  int checkIfSocket(int socketNumber);
  void initLists();
}

#ENDIF
