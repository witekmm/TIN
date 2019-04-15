#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>

#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"
#define MAX_MSG_SIZE 256

using namespace std;
int g_flag = 1;
char buffer[256];

int createSocket( string serverIP, sockaddr_in serwer){
    int yes = 1;
    const int clientSocket = socket( AF_INET, SOCK_STREAM, 0 );
    /*
    if( inet_pton( AF_INET, SERWER_IP, & serwer.sin_addr ) <= 0 )
    {
        perror( "inet_pton() ERROR" );
        exit( 1 );
    }
    */
    if( clientSocket < 0 )
    {
        perror( "socket() ERROR" );
        return -1;
    }
    if( setsockopt( clientSocket, SOL_SOCKET, SO_REUSEADDR, & yes, sizeof( int ) ) == - 1 ) {
        perror( "setsockopt" );
        close(clientSocket);
        return -1;
    }
    return clientSocket;
}

int createConnnection(int clientSocket,sockaddr_in* serwer,socklen_t len ){
    if(connect(clientSocket,( struct sockaddr * ) & serwer,len) == -1){
        perror("Cannot connect!\n");
        return 1;
    }
    printf("Connected. Server socket = %d", clientSocket);
    return 0;
}

int commandLine(int* flag){
    while(*flag){
        char tempBuffer[256];
        puts("Input command:");
        scanf("%255s", tempBuffer);
        while ((getchar()) != '\n');
        int leng=strlen(tempBuffer);
        tempBuffer[leng]='\0';
        //daje znać że zapisuję do buffer
        *flag = 2;
        strcpy(buffer , tempBuffer);
        //wiadomosc w buffer - można wysyłać
        *flag = 3;
        //to jest czyszczenie bufora z nadmiarowych znaków
        while(*flag == 3);
    }
}

void serverConnection(int clientSocket , int *flag){
    char checkBuff;

    while(*flag){
        if(recv(clientSocket , &checkBuff , 1 , MSG_PEEK) == 0){
            puts("Connection has ended!");
            *flag = 0;
        }
        if(*flag == 3){
            if(send(clientSocket, &buffer , strlen(buffer) + 1, 0) == -1){
                perror("Cannot send");
                close(clientSocket);
                *flag = 0;
            }

        }
    }
}

void *CLI(void *){ commandLine(&g_flag); }

int main()
{
    sockaddr_in serwer =
    {
        .sin_family = AF_INET,
        .sin_port = htons( SERWER_PORT )
    };
    socklen_t len = sizeof( serwer );

    int clientSocket = createSocket(SERWER_IP , serwer);
    if(!clientSocket) return 1;
    if(createConnnection(clientSocket,&serwer,len)){
        close(clientSocket);
        return 1;
    }

    pthread_t CLIThread;

    if(pthread_create( &CLIThread , NULL, CLI , NULL) != 0){
      perror("Cannot create CLI thread!\n");
      return 1;
    }
    serverConnection(clientSocket , &g_flag);
    close(clientSocket);
    return 0;

    //shutdown( socket_, SHUT_RDWR );
}
