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
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>
#include "../Messages/Message.pb.h"
#include <cstring>
#include <thread>


#define SERWER_PORT 50000
#define SERWER_IP "127.0.0.1"
#define MAX_MSG_SIZE 256

using namespace std;
int g_flag;
int wiadType = 0;

int commandLine(){
    while(g_flag){
        int x = 0;
        puts("1 - loggin");
        puts("Input number: ");
        cin>>x;
        while((getchar()) != '\n');
        g_flag = 2;
        wiadType = x;
        //wiadomosc w buffer - można wysyłać
        g_flag = 3;
        //to jest czyszczenie bufora z nadmiarowych znaków
        while(g_flag == 3);
    }
}

void recvBuffer(int socket){
  int payloadsize;
  char size[4];
  int odebrane = read(socket, size , 4);
  cout<<"ODEBRANO :"<<odebrane<<endl;
  memcpy(&payloadsize , size , 4);
  cout<<"WIELKOSC TO : "<<payloadsize<<endl;
  char * buffer = new char[payloadsize];
  string fullBuffer;
  while(payloadsize != 0 ){
    int received = read(socket, buffer , payloadsize);
    cout<<received<<endl;
    string temp(buffer);
    fullBuffer+=temp;
    payloadsize-=received;
  }
  Message::ClientMessage message;
  message.ParseFromString(fullBuffer);
  if(message.messagetype() != Message::ClientMessage::REPLY){
    cout<<"COS NIE TRYBI"<<endl;
  }
  if(message.reply() == Message::ClientMessage::POSITIVE){
    cout<<"gutgut"<<endl;
  }
  else{
    cout<<"gohagohagoha 3zl"<<endl;
  }
}

void sendBuffer(int socket){
  int bytesToSent = 0;
  string login = "jp2";
  string password = "gmd";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::AUTHORIZATION);
  message.set_authorizationtype(Message::ClientMessage::LOG_IN);
  message.set_login(login);
  message.set_password(password);
  string msg;
  message.SerializeToString(&msg);
  int payloadsize;
  payloadsize = msg.length();
  bytesToSent = payloadsize+4;
  char* buffer = new char[4];
  memcpy(buffer , &payloadsize , 4);
  char *buffer2 = new char[msg.length()];
  strcpy(buffer2 , msg.c_str());
  char *bufferFull = new char[msg.length() + 4];
  strcpy(bufferFull , buffer);
  strcpy(bufferFull+4 , buffer2);
  int bytessentalready=0;
  cout<<"TO SEND:"<<bytesToSent<<endl;
  cout<<"PAYLOAD SIZE:"<<payloadsize<<endl;
  puts("sending");
  while(bytesToSent!=0){
    int bytesSent = write(socket , bufferFull , bytesToSent);
    if(bytesSent!=0) cout<<"IN ONE PART SENT:"<<bytesSent<<endl;
    if(bytesSent==-1){
      perror("CANNOT SEND");
      return;
    }

    bytesToSent -= bytesSent;
    bytessentalready += bytesSent;
    char *buffer3 = new char[bytesToSent];
    strcpy(buffer3 , bufferFull+bytesSent);
    strcpy(bufferFull , buffer3);
    delete[] buffer3;
  }
  puts("SENT");
  delete[] buffer;
  delete[] bufferFull;
}


int main()
{
    g_flag = 1;
    thread cliThread(&commandLine);
    cliThread.detach();

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

    if(connect(clientSocket, (struct sockaddr*)&serwer, len) == -1){
        perror("Cannot connect");
        close(clientSocket);
        exit( 4 );
    }
    //send(clientSocket , &checkServ)
    printf("\nConnected. Server socket = %d\n", clientSocket);

    while(g_flag){

        if(g_flag == 3){
            sendBuffer(clientSocket);
            recvBuffer(clientSocket);
            g_flag = 1;
        }
    }
    close(clientSocket);
    return 0;

}
