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

//#include <pthread.h>

#define MAX_CONNECTION 10
#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"
#define MAX_MSG_SIZE 4000

using namespace std;

struct sockaddr_in{
    sa_family_t    sin_family;
    in_port_t      sin_port;
};

int main()
{
    sockaddr_in serwer =
    {
        .sin_family = AF_INET,
        .sin_port = htons( SERWER_PORT )
    };

    socklen_t len = sizeof( serwer );
    //zmienne współdzielone
    int flag = 1;
    // 1 - serwer słucha
    // 2 - CLI wysłał rozkaz odłączenia gniazda
    // 3 - CLI wysłał prośbę o listę gniazd
    // 4 - CLI wysłał prośbę o numer gniazda serwera
    int flag_error = 0;
    int fd_val = 0;

    int serverSocket = createSocket(SERWER_IP,serwer);
    doBind(serverSocket , serwer);
    doListen(serverSocket);
    doSelect(serverSocket , &flag);

    pthread_t clientThreads[MAX_CONNECTION];

    int rc;
    for(int i = 0; i < MAX_CONNECTION; i++ ) {
      rc = pthread_create(&clientThreads[i], NULL, , (void *) i);

      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
    }

    return 0;
}

void commandLine(int &flag, int &fd_val, int& flag_error){
     string cmd;
     while(flag){
        getline(cin, cmd);
        if(cmd == "exit"){
            *flag = 0;
        }
        else if(cmd == "help"){
            printf("exit - close server and cmd.\n");
            printf("list - show active sockets.\n");
            printf("server - show server socket number.\n");
            printf("close - disconnect socket.\n");
        }
        else if(cmd == "close"){
            int fdval = 0;
            printf("Which socket:");
            scanf("%d", fdval);
            while ((getchar()) != '\n');
            *fd_val = fdval;
            *flag = 2;
            while(*flag == 2); //czekamy az drugi wątek zamknie
            //Taki socket nie istnieje
            if(*flag_error == 1) printf("Cant find this socket!\n");
            //Probujemy zamknac np. serwer
            else if(*flag_error == 2) printf("You can't close this socket!\n");
            else printf("Socket closed :)\n");
        }
        else if(cmd == "list"){
            *flag = 3;
            int lastfd = 0;
            while(*flag == 3){
                if((*fd_val != 0) && (*fd_val != lastfd)){ //sprawdz czy juz zapisal i czy my go zapisalismy
                    printf("%d\t", *fd_val); //wypisz fd
                    lastfd = *fd_val; // zapisz ostatni fd
                    *fd_val=0; //wyczyszczenie fd_val dla kolejnego numeru fd
                }
            }
        }
        else if(cmd == "server"){
            *flag = 4;
            while(*flag == 4);
            printf("Server socket number is %d", *fd_val);
            *fd_val = 0;
        }
        else{
            printf("Cannot recognize this command!\n");
        }
     }

}

int createSocket( int serverIP, sockaddr_in serwer){
    int yes = 1;
    int no = 0;

    if( inet_pton( AF_INET, serverIP, & serwer.sin_addr ) <= 0 ){
        perror( "inet_pton() ERROR" );
        return -1;
    }

    const int serverSocket = socket( AF_INET, SOCK_STREAM, 0 );

    if( serverSocket < 0 ){
        perror( "socket() ERROR" );
        return -1;
    }

    if( setsockopt( serverSocket, SOL_SOCKET, SO_OOBINLINE, & no, sizeof( int ) ) == - 1 ) {
        perror( "setsockopt" );
        close(serverSocket);
        return -1;
    }
    // Funkcja która sprawi że będziemy mogli ominąć TIME_WAIT i bez przeszkód bo nieoczekiwanym
    // końcu serwera znów zbindować socket
    /*
    if( setsockopt( serverSocket, SOL_SOCKET, SO_REUSEADDR, & yes, sizeof( int ) ) == - 1 ) {
        perror( "setsockopt" );
        exit( 1 );
    }
    */
    return serverSocket;
}

int doBind(int serverSocket, sockaddr_in serwer){
    if( bind( serverSocket,( struct sockaddr * ) & serwer, len ) < 0 ){ // przypisanie lokalnego adresu do gniazda
        perror( "bind() ERROR" );
        close(serverSocket);
        return -1;
    }
    return 0;
}

int doListen(int serverSocket){
    if( listen( serverSocket, MAX_CONNECTION ) < 0 ){
        perror( "listen() ERROR" );
        close(serverSocket);
        return -1;
    }
    return 0;
}

int closeClientSocket(fd_set &master,int socketNumber, int fdmax){
    close(socketNumber);
    FD_CLR(socketNumber , &master);
    int max = fdmax;
    if(socketNumber == fdmax){
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
    printf("Connection with %d has ended.\n", socketNumber);
    return max;
}

void doSelect(int serverSocket, int& flag, int& fd_val, int& flag_error){

    struct timeval tv;
    tv.tv_sec=1;
    tv.tv_usec=0;
    fd_set master; // główna lista deskryptorów plików
    FD_ZERO(& master);
    FD_SET( serverSocket, & master );
    fd_set receivefds; //pomocnicza lista deskryptorów dla select()

    int fdmax;
    int newfd;
    int addrlen;

    int select_value = 0;

    char buf[MAX_MSG_SIZE];

    fdmax = serverSocket;

    while( *flag )
    {
        FD_ZERO(& receivefds);
        receivefds = master;
        struct sockaddr_in client = { };
        //obsługa CLI
        if(*flag != 1){
            if(*flag == 2){//zamknij proces
                while(*fd_val==0);
                if(FD_ISSET(*fd_val, &master)){
                    if(*fd_val == serverSocket){//próbujemy zamknac serwer
                        *flag_error = 2;
                        *flag = 1;
                    }
                    else{
                        fdmax = closeClientSocket(&master,*fd_val,fdmax);
                        *flag = 1;
                    }
                }
                else{
                    *flag = 1;
                    *flag_error = 1;
                }
            }
            else if(*flag == 3){
                for(int i = 0; i<=fdmax;i++){
                    if(FD_ISSET(i, &master)){
                        *fd_val = i;
                        while(*fd_val != 0);
                    }

                }
                *flag = 1;
            }
            else if(*flag == 4){
                *fd_val = serverSocket;
                *flag = 1;
            }
        }
        //Obsługa klientów
        select_value = select( fdmax + 1, &receivefds, NULL, NULL,  &tv)
        if(select_value == - 1 ) {
            perror( "Select error" );
            continue;
        }
        //jeśli coś się stało podczas selecta to sprawdzamy co jeśli nie to continue
        if(!select_value) {
            continue;
        }
        for(int i = 0; i <= fdmax; i++ ) {
            if( FD_ISSET( i, & receivefds ) ) {
                if( i == serverSocket ) { //NOWE POŁĄCZENIE
                    addrlen = sizeof( client );
                    if(( newfd = accept( serverSocket , ( struct sockaddr * )& client, (socklen_t *) &addrlen ) ) == - 1 ) {
                        perror( "accept" );
                    } else {
                        FD_SET( newfd, & master ); // dodaj do głównego zestawu
                        if( newfd > fdmax ) { // śledź maksymalny
                            fdmax = newfd;
                        }
                        printf( "selectserver: new connection from %s on socket %d\n", inet_ntoa( client.sin_addr ), newfd );
                    }
                }
                else{
                    if(recv(i , &buf , 256 , 0) < 0){
                        perror("Cannot receive message");
                        break;
                    }
                    string mess(buf);
                    if(mess == "exit"){
                        closeClientSocket(&master,i,fdmax);
                    }
                    else if(mess == "close"){
                        *flag = 0;

                    }
                    else{
                        for(int s = 0; s<256;s++){
                            if(buf[s] == '\0') break;
                            printf("%c", buf[s]);
                        }
                    }
                }
                break;
            }/*
            if( FD_ISSET( i, & exceptionsfds ) ){

            // tutaj klient wysłał dane OOB
                string msg;
                recv(i , &msg , 1 , MSG_OOB);
                if(msg == "1"){
                    close(i);
                    FD_CLR(i , &master);
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
            }*/

        }
    }
      printf("Server will be closed.\n");
      for(int x = 0 ; x<=fdmax ; x++){
          if(FD_ISSET(x , &master) && x!=serverSocket){
              printf("Connection with %d has ended.\n", x);
              close(x);
           }
      }
      FD_ZERO(&master);
      shutdown( serverSocket, SHUT_RDWR );
      close(serverSocket);
      printf("Server is sleeping.\n");
      return 0;
}
