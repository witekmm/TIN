#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>

#include "Handling.hpp"

#include "../server/Server.hpp"

#define MAX_MSG_SIZE 256
#define SERWER_PORT 50000

using namespace std;

Handling *handler;
void* start(void *){ handler->run(); }

int main(int argc, char*argv[])
{
    int port = SERWER_PORT;
    if(argc == 2){
        int port = atoi(argv[2]);
        if(port < 49152 || port >65535){
            puts("Wrong port!");
            puts("Port will be set automatically.");
            port = SERWER_PORT;
        }
    }

    Server server(port;

    if(inet_pton(AF_INET, SERWER_IP, &server.getServer().sin_addr) <= 0)
    {
        perror( "inet_pton() ERROR" );
        exit(1);
    }

    const int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0)
    {
        perror( "socket() ERROR" );
        exit(2);
    }

    if(connect(clientSocket, (struct sockaddr*)&server.getServer(), server.getLen()) == -1){
        perror("Cannot connect");
        close(clientSocket);
        exit(4);
    }

    cout<<"\nConnected. Server socket = "<<clientSocket<<endl;

    fcntl(clientSocket, F_SETFL, O_NONBLOCK);

    int clientSocket = 1;
    handler = new Handling(clientSocket);

    // wątek do obsługi wysyłania wiadomości i sprawdzania połączenia z serwerem
    pthread_t CLIThread;
    if(pthread_create(&CLIThread, NULL, start, NULL) != 0){
      perror("Cannot create CLI thread!\n");
      return 1;
    }
    // uruchamia się pętla do obsługi terminala na wątku głównym
    handler->input();

    close(clientSocket);
    delete handler;
    return 0;

}
