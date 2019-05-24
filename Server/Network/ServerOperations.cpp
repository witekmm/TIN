#include "ServerOperations.h"

ServerOperation::ServerOperation(int maxConnections, int port, std::string ip): maxConnections(maxConnections), port(port), serverIP(ip) , socketNumber(0), isSocketNumberSet(false), isSocketListening(false){
  this->serverAddress.sin_family = AF_INET;
  std::cout<<"Port number is:"<<port<<std::endl;
  this->serverAddress.sin_port = htons(port);
  this->len = sizeof(this->serverAddress);
  char temp[ip.length() + 1];
  strcpy(temp , ip.c_str());
  std::cout<<"Server IP Address is:"<<temp<<std::endl;
  if( inet_pton(AF_INET, temp , &this->serverAddress.sin_addr) <= 0){
    perror("Wrong ip address!");
  }
}

int ServerOperation::createServerSocket(){
  int yes = 1;
  this->socketNumber = socket(AF_INET, SOCK_STREAM, 0);
  if(this->socketNumber < 0){
    perror("Cannot create socket");
    return -1;
  }
  if(setsockopt(this->socketNumber, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == - 1){
    perror("Cannot set option!");
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  puts("Socket created.");
  return this->socketNumber;
}

int ServerOperation::bindServerSocket(){
  if( bind(this->socketNumber, (struct sockaddr*)&(this->serverAddress), this->len) < 0){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    perror("Cannot bind adres to socket!");
    return -1;
  }
  else{
    this->isSocketNumberSet=true;
    puts("Socket binded to IP.");
    return 0;
  }
}

int ServerOperation::listenServerSocket(){
  if(listen(this->socketNumber, this->maxConnections) < 0){
    shutdown(this->socketNumber, SHUT_RDWR);
    close(this->socketNumber);
    return -1;
  }
  else{
    this->isSocketListening=true;
    puts("Socket is passive.\n");
    return 0;
  }
}

int ServerOperation::acceptConnection(){
  struct sockaddr_in client = {};
  socklen_t addrlen = sizeof( client );
  //połaczenie nieblokujące
  int newfd = accept4(this->socketNumber, (struct sockaddr*)&client, &addrlen, SOCK_NONBLOCK);
  //Brak połączenia
  if(newfd == -1) return -1;
  //Połączono
  else return newfd;
}

int ServerOperation::getSocketNumber(){
  return this->socketNumber;
}

void ServerOperation::setPort(int port){
  this->port = port;
}

bool ServerOperation::getIsSocketNumberSet(){
  return this->isSocketNumberSet;
}

void ServerOperation::closeServer(){
  this->socketNumber=0;
  this->isSocketNumberSet=false;
  this->isSocketListening=false;
}
bool ServerOperation::getIsSocketListening(){
  return this->isSocketListening;
}
