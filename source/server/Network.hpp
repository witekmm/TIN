#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

#include "Output.hpp"
#include "Handling.hpp"

class Network{
    int serverSocket;

public:
    //konstruktor
    Network(int socketNumbet){
        serverSocket = socketNumber;
    }
    //Połącz z klientem
    int connectClient(fd_set &socketList){
        int newfd = accept(serverSocket, (struct sockaddr*)&client, (socklen_t *)&addrlen))
        if( newfd == -1){

        }

    }

}
