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
#include <arpa/inet.h>#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>

#include "Server.hpp"


#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"
#define MAX_MSG_SIZE 256

using namespace std;
int g_flag = 1;
char buffer[256];

int commandLine(int* flag){
    while(*flag){
        char tempBuffer[256];
        printf("Input command: ");
        scanf("%255s", tempBuffer);
        while((getchar()) != '\n');
        int leng = strlen(tempBuffer);
        tempBuffer[leng] = '\0';
        //daje znać że zapisuję do buffer
        *flag = 2;
        strcpy(buffer, tempBuffer);
        //wiadomosc w buffer - można wysyłać
        *flag = 3;
        //to jest czyszczenie bufora z nadmiarowych znaków
        while(*flag == 3);
    }
}

void *CLI(void *){ commandLine(&g_flag); }

int main(int argc, char*argv[])
{
    pthread_t CLIThread;
    if(pthread_create(&CLIThread, NULL, CLI, NULL) != 0){
      perror("Cannot create CLI thread!\n");
      return 1;
    }
    if(argc != 2){
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
    //send(clientSocket , &checkServ)
    printf("\nConnected. Server socket = %d\n", clientSocket);
    fcntl(clientSocket, F_SETFL, O_NONBLOCK);

    while(g_flag){

        if(g_flag == 3){
            if(send(clientSocket, &buffer, strlen(buffer) + 1, 0) == -1){
                perror("Cannot send");
                //close(clientSocket);
                g_flag = 0;
            }
            if((string)buffer == "exit"){
              cout<<"Closing client"<<endl;
              if( recv(clientSocket, NULL, 1, 0) == 0){
                break;
              }
            }
            g_flag = 1;
        }
        else if( recv(clientSocket, NULL, 1, 0) == 0){
          cout<<"\nServer signal. \nClosing client"<<endl;
          break;
        }
    }
    close(clientSocket);
    return 0;

}
