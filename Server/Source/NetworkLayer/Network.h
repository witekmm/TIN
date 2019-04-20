#IFNDEF NETWORK_H
#DEFINE NETWORK_H
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <algorithm>

class Network{
  //Descriptors list:
  //master - original list
  //readfds - waiting for read action
  //writefds - waiting for write action
  //exceptionfds - waiting for exception signals
  fd_set master, readfds, writefds, exceptionfds;
  //transport address and port
  sockaddr_in server{};
  socklen_t len;
  //list of active sockets
  std::vector<int> activeSockets;
  int sockets;
  //Maximal descriptor number
  int fdmax;
  //Server socket number
  int serverSocket;
  //max connections pending on for accept
  int maxConnections;
public:
  Network();
  //server configure
  int createServerSocket();
  int bindServerSocket();
  int listenServerSocket();
  //0 if accept gone well, 1 if not
  int acceptConnection();
  //signal from sockets
  void selectDescriptor();
  //Close choosen socket
  int closeSocket(int socketNumber);
  //Find new fdmax after closing the old one
  void updateFdmax();
  //Clears choosen socket from activeSockets and decreases sockets
  void clearSocket(int socketNumber);
  //return 0 if socket , 1 if not
  int checkIfSocket(int socketNumber);
  //Clears waiting lists
  void clearLists();
}

#ENDIF
