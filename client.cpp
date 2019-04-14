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

#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"

using namespace std;

int main()
{
    struct sockaddr_in serwer =
    {
        .sin_family = AF_INET,
        .sin_port = htons( SERWER_PORT )
    };
    if( inet_pton( AF_INET, SERWER_IP, & serwer.sin_addr ) <= 0 )
    {
        perror( "inet_pton() ERROR" );
        exit( 1 );
    }

    const int clientSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if( clientSocket < 0 )
    {
        perror( "socket() ERROR" );
        exit( 2 );
    }

    socklen_t len = sizeof( serwer );
    // if( bind( clientSocket,( struct sockaddr * ) & serwer, len ) < 0 )
    // {
    //     perror( "bind() ERROR" );
    //     exit( 3 );
    // }

    printf( "Waiting for connection...\n" );

    //struct sockaddr_in client = { };

    if(connect(clientSocket,( struct sockaddr * ) & serwer,len) == -1){
        perror("Cannot connect");
        exit( 4 );
    }
    cout<<"socket: "<<clientSocket<<endl;
    printf("Connected.\n" );

    while(1){
        std::string command;
        sleep(1);
        printf("Input command:");
        cin>>command;
        if(command == "send"){
            char buffer[256];
            cout<<"Input message text:";
            scanf("%s", buffer);
            if(send(clientSocket, &buffer , 4 , 0) == -1){
                perror("Cannot send");
                exit( 5 );
            }
        }
        if(command == "exit"){
            char stop[] = "1";
            if(send(clientSocket, &stop , sizeof(stop) , MSG_OOB) == -1){
                perror("Cannot send");
                exit( 5 );
            }
            sleep(1);
            //break;

        }

    }


    //shutdown( socket_, SHUT_RDWR );
}
