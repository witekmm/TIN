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
        perror("Cannon connect");
        exit( 4 );
    }

    printf("Connected.\n" );

    string buffer = "1";

    sleep(2);
    send(clientSocket, &buffer , 1 , MSG_OOB);



    /*
    const int clientSocket = accept( socket_,( struct sockaddr * ) & client, & len );
        if( clientSocket < 0 )
        {
            perror( "accept() ERROR" );
            continue;
        }

        char buffer[ MAX_MSG_LEN ] = { };

        if( recv( clientSocket, buffer, sizeof( buffer ), 0 ) <= 0 )
        {
            perror( "recv() ERROR" );
            exit( 5 );
        }
        printf( "|Message from client|: %s \n", buffer );

        strcpy( buffer, "Message from server" );
        if( send( clientSocket, buffer, strlen( buffer ), 0 ) <= 0 )
        {
            perror( "send() ERROR" );
            exit( 6 );
        }

        shutdown( clientSocket, SHUT_RDWR );
    */

    //shutdown( socket_, SHUT_RDWR );
}
