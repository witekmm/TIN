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

//#include "../server/Server.hpp"

#define MAX_MSG_SIZE 256

using namespace std;

Handling *handler;
void* start(void *){ handler->run(); }

int main(int argc, char*argv[])
{
  /*  if(argc != 2){
        perror("No port given");
        exit(0);
    }

    Server server(atoi(argv[1]));

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

    printf("\nConnected. Server socket = %d\n", clientSocket);
    cout<<"\nConnected. Server socket = "<<clientSocket<<endl;
    
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);
*/
    int clientSocket = 1;
    handler = new Handling(clientSocket);
    
    pthread_t CLIThread;
    if(pthread_create(&CLIThread, NULL, start, NULL) != 0){
      perror("Cannot create CLI thread!\n");
      return 1;
    }
    
    handler->input();

    close(clientSocket);
    delete handler;
    return 0;

}
