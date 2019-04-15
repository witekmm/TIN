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
    int serverStatus;
    int serverStatusSize = sizeof(serverStatus);

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

    printf( "Waiting for connection...\n" );

    if(connect(clientSocket,( struct sockaddr * ) & serwer,len) == -1){
        perror("Cannot connect");
        exit( 4 );
    }
    cout<<"socket: "<<clientSocket<<endl;
    printf("Connected.\n" );
    char buffer[256] = "start";
    while(strcmp(buffer,"stop")!=0){
        std::string command;
        cout<<"Input message:";
        scanf("%255s", buffer);
        int leng=strlen(buffer);
        buffer[leng]='\0';
        //to jest czyszczenie bufora z nadmiarowych znaków
        while ((getchar()) != '\n');
        if(send(clientSocket, &buffer , strlen(buffer) + 1, 0) == -1){
            //Nie mogę wysłać bo pewnie połączenie zostało zerwane
            //więc idę spać
            perror("Cannot send");
            close(clientSocket);
            exit( 5 );
        }

    }
    //buffer = "exit";
    if(send(clientSocket, "exit" , 5, 0) == -1){
        perror("Cannot exit");
        close(clientSocket);
        exit( 6 );
    }
    close(clientSocket);

    return 0;

    //shutdown( socket_, SHUT_RDWR );
}
