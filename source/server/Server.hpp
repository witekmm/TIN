#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

#include "Network.hpp"

#define SERVER_IP "127.0.0.1"
#define MAX_CONNECTION 10


class Server{

  sockaddr_in server{};
  socklen_t len;

public:


  Server(int port){
    server.sin_family = AF_INET,
    server.sin_port = htons(port);
    len = sizeof(server);
  }

  sockaddr_in &getServer(){
    return this->server;
  }

  int createSocket()
  {
      int yes = 1;

      const int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

      if(serverSocket < 0){
          perror( "socket() ERROR" );
          return -1;
      }

      if(setsockopt( serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == - 1 ) {
          perror( "setsockopt" );
          return -1;
      }
      return serverSocket;
  }

  int doBind(int serverSocket)
  {
      if( bind(serverSocket, (struct sockaddr*) &(this->server), this->len) < 0)
      {
          perror( "bind() ERROR" );
          close(serverSocket);
          return -1;
      }
      return 0;
  }

  int doListen(int serverSocket){
      if( listen( serverSocket, MAX_CONNECTION ) < 0 ){
          perror( "listen() ERROR" );
          close(serverSocket);
          return -1;
      }
      return 0;
  }

  void doSelect(int serverSocket){
      Network network(serverSocket);

      fd_set master;
      fd_set receivefds;
      fd_set efds;

      FD_ZERO(& master);
      FD_SET( serverSocket, & master );

      int fdmax;

      while( cos ){
          FD_ZERO(&receivefds);
          receivefds = master;
          FD_ZERO(&efds);
          efds = master;

          if(select(fdmax+1, &receivefds, NULL, &efds, NULL) == -1){
              perror("Select error");
              continue;
          }
          for(int socketNumber = 0; socketNumber <= fdmax; socketNumber++ ) {
              if( FD_ISSET(socketNumber , &receivefds) ) {
                  //NOWE POŁĄCZENIE
                  if(socketNumber == serverSocket) fdmax = network.connectClient(&master , fdmax);
                  //INTERAKCJA Z UŻYTKOWNIKIEM
                  else network.readHeader(socketNumber);
              if( FD_ISSET(socketNumber , &efds) ){
                  //DO ZROBIENIA
              }
          }
      }
  }

};
