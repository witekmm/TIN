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

using namespace std;

class Server{

    sockaddr_in server{};
    socklen_t len;

    int working;

    fd_set master;
    int fdmax;
    Network& network;

    int serverSocket;
public:

    Server(int port){
      server.sin_family = AF_INET,
      server.sin_port = htons(port);
      len = sizeof(server);
    }

    void setNetwork(Network &netw){
        network = netw;
    }

    void stopServer(){
        working = 1;
    }

    sockaddr_in &getServer(){
      return this->server;
    }

    socklen_t &getLen(){
      return this->len;
    }

    int createSocket()
    {
        int yes = 1;
        const int serverSock = socket(AF_INET, SOCK_STREAM, 0);

        if(serverSocket < 0){
            perror( "socket() ERROR" );
            return -1;
        }

        if(setsockopt( serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == - 1 ) {
            perror( "setsockopt" );
            return -1;
        }
        serverSocket = serverSock;
        return serverSock;
    }

    int doBind()
    {
        if( bind(serverSocket, (struct sockaddr*) &(this->server), this->len) < 0)
        {
            perror( "bind() ERROR" );
            close(serverSocket);
            return -1;
        }
        return 0;
    }

    int doListen(){
        if( listen( serverSocket, MAX_CONNECTION ) < 0 ){
            perror( "listen() ERROR" );
            close(serverSocket);
            return -1;
        }
        return 0;
    }

    void *doSelect(){

        fd_set receivefds;
        fd_set efds;

        FD_ZERO(& master);
        FD_SET( serverSocket, & master );

        while( working ){
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
                    else network.readMessage(socketNumber);
                }
                else if( FD_ISSET(socketNumber , &efds) ){
                    network.exceptionSignal(socketNumber);
                }

            }//END OF FOR
        }//END OF WHILE
    }

// -2 - zamykamy serwer więc błąd
// -1 - nie istnieje taki klient
// 0 dobrze
    int closeSocket(int socketNumber){
        if(socketNumber == serverSocket) return -2;
        if(!FD_ISSET(socketNumber , &master)) return -1;

        if(socketNumber == fdmax) fdmax = findNewFDMax(fdmax);
        shutdown(socketNumber, SHUT_RDWR);
        close(socketNumber);
        FD_CLR(socketNumber, &master);

        return 0;
    }

    int findNewFDMax(int oldMax){
        int max = 0;
        for(int x = oldMax-1; x>0 ;x--){
          if(FD_ISSET(x, &master) == 1){
            max=x;
            break;
          }
        }

      return max;
    }

    int getFdMax(){
      return fdmax;
    }

    int checkIfSocket(int socketNumber){
        if(FD_ISSET(socketNumber , &master)) return 0;
        else return -1;
    }

    void closeServerSocket(){
      FD_ZERO(&master);
      shutdown( serverSocket, SHUT_RDWR );
      close(serverSocket);
    }

}
