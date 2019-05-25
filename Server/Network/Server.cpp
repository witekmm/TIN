#include "NetLibs.h"
#include "Server.h"
using namespace std;

Server::Server()
  : Server(DEFAULT_MAX_CONNECTIONS, DEFAULT_SERVER_PORT, DEFAULT_SERVER_IP){}

Server::Server(int maxConnections, int port, string ip)
{
  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_port = htons(port);
  this->len = sizeof(this->serverAddress);
  this->maxConnections = maxConnections;
  this->port = port;
  this->serverIP = ip;
}

int Server::createServerSocket()
{
  if( inet_pton(AF_INET, (char*)&serverIP, &serverAddress.sin_addr) <= 0){
    return -1;
  }
  int yes = 1;
  socketNumber = socket(AF_INET, SOCK_STREAM, 0);
 
  if(socketNumber < 0) 
    return -1;
  if(setsockopt(socketNumber, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
  {
    shutdown(socketNumber, SHUT_RDWR);
    close(socketNumber);
    return -1;
  }
  return socketNumber;
}

int Server::bindServerSocket()
{
  if( bind(socketNumber, (struct sockaddr*)&serverAddress, len) < 0) 
  {
    shutdown(socketNumber, SHUT_RDWR);
    close(socketNumber);
    return -1;
  }
  else return 0;
}

int Server::listenServerSocket()
{
  if(listen(socketNumber, maxConnections) < 0)
  {
    shutdown(socketNumber, SHUT_RDWR);
    close(socketNumber);
    return -1;
  }
  else return 0;
}

int Server::acceptConnection()
{
  struct sockaddr_in client = {};
  socklen_t addrlen = sizeof(client);
  //połaczenie nieblokujące
  int newfd = accept4(socketNumber, (struct sockaddr*)&client, &addrlen, SOCK_NONBLOCK);
  if(newfd == -1)  //Brak połączenia
    return -1;
  else return newfd; //Połączono
}

int Server::getSocketNumber(){
  return this->socketNumber;
}
