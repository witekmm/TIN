#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "Server.hpp"

#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"
#define MAX_MSG_SIZE 256

#import "Handling.hpp"

using namespace std;

int main(int argc, char*argv[])
{
    int port;
    if(argc == 1){
        //port hardcoded
    }
    else if(argc == 2){
        int port = atoi(argv[2]);
        if(port < 49152 || port >>65535){
            puts("Wrong port!");
            puts("Port will be set automatically.");
            port = SERWER_PORT;
        }
    }
//warstwa aplikacji/prezentacji
    Output output();
    CLI cli();
//warstwa łącza danych
    Server server(port);
    int serverSocket = server.createSocket();
    if(serverSocket == -1) return 1;
    if(server.doBind() == -1) return 1;
    if(server.doListen() == -1) return 1;
//warstwa sieciowa
    Network network(serverSocket , server);
    server.setNetwork(network);
//warstwa transportowa
    Handling handling(cli,output,network);
    network.setHandling(handling);
//podpięcie cli do handling
    cli.setHandling(handling);

    pthread_t serverThread;
    if(pthread_create( &serverThread , NULL, server.doSelect , NULL) != 0){
      perror("Cannot create server thread!\n");
      return 1;
    }

    cli.commandLine();

    return 0;
}
