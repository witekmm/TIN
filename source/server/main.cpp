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

using namespace std;

//zmienne współdzielone
int g_flag = 1;
// 1 - serwer słucha a CLI nie wymaga komunikacji z serwerem
// 2 - CLI wysłał rozkaz odłączenia gniazda
// 3 - CLI wysłał prośbę o listę gniazd
// 4 - CLI wysłał prośbę o numer gniazda serwera
int g_flag_error = 0;
int g_fd_val = 0;
/* być może tak trzeba będzie przekazać argumenty do funkcji
commandLine(wsk_flag,wsk_flag_error,wsk_fd_val);
int *wsk_flag = &dlugosc;
int *wsk_flag_error = &flag_error;
int *wsk_fd_val = &fd_val;
*/


void *CLI(void *){ commandLine(&g_flag, &g_fd_val, &g_flag_error); }

int closeClientSocket(fd_set &master, int socketNumber, int fdmax){
    shutdown(socketNumber, 2);
    close(socketNumber);
    FD_CLR(socketNumber, &master);
    int max = fdmax;
    if(socketNumber == fdmax)
    {
        max = 0;
        for(int x = fdmax-1; x>0 ;x--)
        {
          if(FD_ISSET(x, &master) == 1)
          {
            max=x;
            break;
          }
        }
    }
    printf("\nConnection with %d has ended.\n", socketNumber);
    return max;
}

void doSelect(int serverSocket, int *flag, int *fd_val, int *flag_error){

    struct timeval tv;);
    tv.tv_sec=1;
    tv.tv_usec=0;
    fd_set master; // główna lista deskryptorów plików
    FD_ZERO(& master);
    FD_SET( serverSocket, & master );
    fd_set receivefds; //pomocnicza lista deskryptorów dla select()
    int fdmax, newfd, addrlen, select_value=0;
    char buf[MAX_MSG_SIZE];
    fdmax = serverSocket;

    while( *flag )
    {
        FD_ZERO(&receivefds);
        receivefds = master;

        //Obsługa klientów
        struct sockaddr_in client = { };
        select_value = select(fdmax+1, &receivefds, NULL, NULL, &tv);
        if(select_value == -1) {
            perror("Select error");
            continue;
        }
        //jeśli coś się stało podczas selecta to sprawdzamy co jeśli nie to continue
        if(!select_value) {
            continue;
        }
        for(int i = 0; i <= fdmax; i++ ) {
            if( FD_ISSET(i, &receivefds) ) {
                if(i == serverSocket) { //NOWE POŁĄCZENIE
                    addrlen = sizeof( client );
                    if(( newfd = accept(serverSocket, (struct sockaddr*)&client, (socklen_t *)&addrlen)) == -1) {
                        perror( "accept" );
                    }
                    else {
                        FD_SET( newfd, &master ); // dodaj do głównego zestawu
                        if( newfd > fdmax ) { // śledź maksymalny
                            fdmax = newfd;
                        }
                        printf("\nServer: new connection from %s on socket %d\n", inet_ntoa( client.sin_addr ), newfd );
                        puts("Input command:");
                    }
                }
                else { // KLIENT CHCE PISAC
                    if(recv(i , &buf , 256 , 0) < 0){
                        perror("Cannot receive message");
                        break;
                    }
                    string mess(buf);
                    if(mess == "exit"){
                        closeClientSocket(master, i, fdmax);
                    }
                    else if(mess == "close"){
                        *flag = 0;
                    }
                    else{//Przyszła zwykła wiadomość
                        printf("\nThe message from %d is: ", i);
                        for(int s = 0; s<256; s++){
                            if(buf[s] == '\0') break;
                            printf("%c", buf[s]);
                        }
                        bzero(buf, 256);
                        puts("\nInput command:");
                    }
                }
            }
        }
    }
    puts("\nServer will be closed.");
    for(int x = 0 ; x<=fdmax ; x++){
        if(FD_ISSET(x, &master) && x!=serverSocket){
          printf("\nConnection with %d has ended.\n", x);
          close(x);
        }
    }
    FD_ZERO(&master);
    shutdown( serverSocket, SHUT_RDWR );
    close(serverSocket);
    printf("Server is sleeping.\n");
}

int main(int argc, char*argv[])
{
    if(argc != 2){
        perror("No port given");
        exit(0);
    }

    Server server(atoi(argv[1]));

    pthread_t CLIThread;
    if(pthread_create( &CLIThread , NULL, CLI , NULL) != 0){
      perror("Cannot create CLI thread!\n");
      return 1;
    }

    int serverSocket = server.createSocket();
    server.doBind(serverSocket);
    server.doListen(serverSocket);
    doSelect(serverSocket , &g_flag, &g_fd_val, &g_flag_error);

    return 0;
}
