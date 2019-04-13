#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // strlen()
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>

#define MAX_CONNECTION 10
#define SERWER_PORT 50000

int main()
{

    fd_set master; // główna lista deskryptorów plików
    fd_set exceptionsfds; // pomocnicza lista deskryptorów dla select()
    int fdmax;
    int newfd;
    int addrlen;
    FD_ZERO(& master);
    FD_ZERO(& exceptionsfds);

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
        struct sockaddr_in client = { };

        if( select( fdmax + 1, NULL, NULL, &exceptionsfds, NULL ) == - 1 ) {
            perror( "select" );
            exit( 1 );
        }

        for( i = 0; i <= fdmax; i++ ) {
            if( FD_ISSET( i, & excptionsfds ) ) { // mamy jednego!!
                if( i == serverSocket ) {
                    // obsłuż nowe połączenie
                    addrlen = sizeof( client );
                    if(( newfd = accept( listener,( struct sockaddr * ) & remoteaddr,
                    & addrlen ) ) == - 1 ) {
                        perror( "accept" );
                    } else {
                        FD_SET( newfd, & master ); // dodaj do głównego zestawu
                        if( newfd > fdmax ) { // śledź maksymalny
                            fdmax = newfd;
                        }
                        printf( "selectserver: new connection from %s on "
                        "socket %d\n", inet_ntoa( remoteaddr.sin_addr ), newfd );
                    }
                } else {
                    // obsłuż dane od klienta
                    if(( nbytes = recv( i, buf, sizeof( buf ), 0 ) ) <= 0 ) {
                        // błąd lub połączenie zostało zerwane
                        if( nbytes == 0 ) {
                            // połączenie zerwera
                            printf( "selectserver: socket %d hung up\n", i );
                        } else {
                            perror( "recv" );
                        }
                        close( i ); // papa!
                        FD_CLR( i, & master ); // usuń z głównego zestawu
                    } else {
                        // mamy trochę danych od klienta
                        for( j = 0; j <= fdmax; j++ ) {
                            // wyślij do wszystkich!
                            if( FD_ISSET( j, & master ) ) {
                                // oprócz nas i gniazda nasłuchującego
                                if( j != listener && j != i ) {
                                    if( send( j, buf, nbytes, 0 ) == - 1 ) {
                                        perror( "send" );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }





    shutdown( serverSocket_, SHUT_RDWR );


    return 0;
}
