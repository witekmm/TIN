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

#define MAX_CONNECTION 10
#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"

using namespace std;

int main()
{

    fd_set master; // główna lista deskryptorów plików
    fd_set exceptionsfds; // pomocnicza lista deskryptorów dla select()
    fd_set receivefds; //pomocnicza lista deskryptorów dla select()
    int fdmax;
    int newfd;
    int addrlen;
    FD_ZERO(& master);
    FD_ZERO(& exceptionsfds);
    FD_ZERO(& receivefds);

    struct sockaddr_in serwer =
    {
        .sin_family = AF_INET,
        .sin_port = htons( SERWER_PORT )
    };
    if( inet_pton( AF_INET, SERWER_IP, & serwer.sin_addr ) <= 0 ){
        perror( "inet_pton() ERROR" );
        exit( 1 );
    }

    const int serverSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if( serverSocket < 0 ){
        perror( "socket() ERROR" );
        exit( 2 );
    }

    socklen_t len = sizeof( serwer );

     if( bind( serverSocket,( struct sockaddr * ) & serwer, len ) < 0 ){ // przypisanie lokalnego adresu do gniazda
        perror( "bind() ERROR" );
        exit( 3 );
    }

    if( listen( serverSocket, MAX_CONNECTION ) < 0 ){
        perror( "listen() ERROR" );
        exit( 4 );
    }

    FD_SET( serverSocket, & master );
    fdmax = serverSocket;

    while( 1 )
    {
        exceptionsfds = master;
        receivefds = master;
        struct sockaddr_in client = { };

        if( select( fdmax + 1, &receivefds, NULL, &exceptionsfds, NULL ) == - 1 ) {
            perror( "select" );
            exit( 1 );
        }

        for(int i = 0; i <= fdmax; i++ ) {
            if( FD_ISSET( i, & receivefds ) ) {
                if( i == serverSocket ) { //NOWE POŁĄCZENIE
                    addrlen = sizeof( client );
                    if(( newfd = accept( serverSocket,( struct sockaddr * ) client, (socklen_t *) &addrlen ) ) == - 1 ) {
                        perror( "accept" );
                    } else {
                        FD_SET( newfd, & master ); // dodaj do głównego zestawu
                        if( newfd > fdmax ) { // śledź maksymalny
                            fdmax = newfd;
                        }
                        printf( "selectserver: new connection from %s on socket %d\n", inet_ntoa( client.sin_addr ), newfd );
                    }
                }
                else { //WIADOMOSC OD KOGOS A W TEJ WIADOMOSCI

                }
            }
            if( FD_ISSET( i, & exceptionsfds ) ){
            // tutaj klient wysłał dane OOB
                string msg;
                recv(i , &msg , 1 , MSG_OOB);
                if(strcmp((char *) &msg , "1")){
                    close(i);
                    FD_CLR(i , &master);
                    if(i==fdmax){
                        int * x = master;
                        int best = &master;
                        while(x != NULL){
                            if(*x == fdmax) continue;
                            if(*x > best) best = *x;
                            x++;
                        }
                        fdmax = best;
                    }
                }
                if(strcmp((char *) &msg,"0")){
                    for(int * x = master; x!= NULL; x++){
                        if(*x == serverSocket) continue;
                        close(i);
                    }
                    FD_ZERO(master);
                    shutdown( serverSocket, SHUT_RDWR );
                    close(serverSocket);
                    return 0;
                }
            }
        }
    }



    shutdown( serverSocket, SHUT_RDWR );
    close(serverSocket);

    return 0;
}
