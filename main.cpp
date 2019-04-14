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
 #include <signal.h>
#include <pthread.h>

//#include <pthread.h>

#define MAX_CONNECTION 10
#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"
#define MAX_MSG_SIZE 1

using namespace std;


void handle_sigint(int sig)
{
    printf("Caught signal %d\n", sig);
}

int main()
{

    fd_set master; // główna lista deskryptorów plików
    fd_set exceptionsfds; // pomocnicza lista deskryptorów dla select()
    fd_set receivefds; //pomocnicza lista deskryptorów dla select()
    int fdmax;
    int newfd;
    int addrlen;
    int yes = 1;
    int no = 0;
    char buf[MAX_MSG_SIZE];
    FD_ZERO(& master);
    FD_ZERO(& exceptionsfds);
    FD_ZERO(& receivefds);
/*
    pthread_t clientThreads[MAX_CONNECTION];
    int rc;
    for(int i = 0; i < MAX_CONNECTION; i++ ) {
      rc = pthread_create(&clientThreads[i], NULL, NULL, (void *)i);

      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
*/
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

    if( setsockopt( serverSocket, SOL_SOCKET, SO_OOBINLINE, & no, sizeof( int ) ) == - 1 ) {
        perror( "setsockopt" );
        exit( 1 );
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
        cout<<"100"<<endl;
        FD_ZERO(& exceptionsfds);
        cout<<"a"<<endl;
        FD_ZERO(& receivefds);
        exceptionsfds = master;
        cout<<"b"<<endl;
        receivefds = master;
        cout<<"c"<<endl;
        struct sockaddr_in client = { };

        if( select( fdmax + 1, &receivefds, NULL, &exceptionsfds, NULL ) == - 1 ) {
            perror( "select" );
            exit( 1 );
        }
        cout<<"111"<<endl;
        for(int i = 0; i <= fdmax; i++ ) {

          cout<<"113"<<endl;
            if( FD_ISSET( i, & receivefds ) ) {
                if( i == serverSocket ) { //NOWE POŁĄCZENIE
                    addrlen = sizeof( client );
                    if(( newfd = accept( serverSocket , ( struct sockaddr * )& client, (socklen_t *) &addrlen ) ) == - 1 ) {
                        perror( "accept" );
                    } else {
<<<<<<< HEAD

=======
>>>>>>> 0f8b3fe4586b3ecfd8165a2b9195af6933ddb6c8
                        FD_SET( newfd, & master ); // dodaj do głównego zestawu
                        if( newfd > fdmax ) { // śledź maksymalny
                            fdmax = newfd;
                        }
                        printf( "selectserver: new connection from %s on socket %d\n", inet_ntoa( client.sin_addr ), newfd );
                    }
                }
                else{
                  cout<<"133"<<endl;
                    if(recv(i , &buf , strlen(buf)+1 , 0) < 0){
                        perror("Cannot receive message");
                        exit(-2);
                    }
                    else{
                      cout<<"138"<<endl;
                        for(int s = 0; s<256;s++){
                            if(buf[s] == '\0') break;
                            printf("%c", buf[s]);
                        }
                        cout<<"144"<<endl;
                    }
                }
            }
            if( FD_ISSET( i, & exceptionsfds ) ){

              cout<<"149"<<endl;
            // tutaj klient wysłał dane OOB
                string msg;
                recv(i , &msg , 1 , MSG_OOB);
                cout<<"154"<<endl;
                cout<<"msg: "<<msg<<endl;
                if(msg == "1"){
                  cout<<"155"<<endl;
                    close(i);
                    FD_CLR(i , &master);
                    cout<<"157"<<endl;
                    if(i==fdmax){
                        int * x = (int*)&master;
                        int best = *x;
                        while(x != NULL){
                            if(*x == fdmax) continue;
                            if(*x > best) best = *x;
                            x++;
                        }
                        fdmax = best+1;
                    }
                    printf("Connection abandonedened by %d", i);
                    break;
                }
                cout<<"169"<<endl;
                if(msg == "0"){
                    printf("Server will be closed");
                    for(int * x = (int*)&master; x!= NULL; x++){
                        if(*x == serverSocket) continue;
                        close(i);
                    }
                    FD_ZERO(&master);
                    shutdown( serverSocket, SHUT_RDWR );
                    close(serverSocket);
                    return 0;
                }
                cout<<"183"<<endl;
            }
        }
    }

    shutdown( serverSocket, SHUT_RDWR );
    close(serverSocket);

    return 0;
}
