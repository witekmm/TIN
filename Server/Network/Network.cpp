#include "NetLibs.h"
#include <thread>
#include <stdio.h>
#include "Network.h"
#include "../Transport/Transport.h"
using namespace std;
Network::Network(Transport& tp):transport(tp), server(){
  this->sockets==0;
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_ZERO(&this->master);
  this->fdmax==0;
}

int Network::startServer(int maxConnections, int port, string ip){
  Server temp(maxConnections, port, ip);
  this->server=temp;
  if(this->server.createServerSocket() == -1) return -1;
  if(this->server.bindServerSocket() == -1) return -1;
  if(this->server.listenServerSocket() == -1) return -1;
  addSocket(server.getSocketNumber());
  return 0;
}

void Network::clearSocket(int socketNumber){
  for(vector<int>::iterator it = this->activeSockets.begin() ; it != this->activeSockets.end(); it++){
    if(*it == socketNumber){
      this->activeSockets.erase(it);
      break;
    }
  }
  for(vector<Client>::iterator it = this->activeClients.begin() ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      this->activeClients.erase(it);
      break;
    }
  }
  this->sockets--;
  FD_CLR(socketNumber , &master);
}

void Network::addSocket(int socketNumber){
  FD_SET(socketNumber , &master);
  this->activeSockets.push_back(socketNumber);
  this->sockets++;
  updateFdmax();
}

void Network::updateFdmax(){
  int max=0;
  for(int i = 0 ; i < this->sockets ; i++){
    if(this->activeSockets[i]>max) max = this->activeSockets[i];
  }
  this->fdmax=max;
}

int Network::checkIfSocket(int socketNumber){
  for(int i = 0;i<this->sockets;i++){
    if(socketNumber==this->activeSockets[i]) return 0;
  }
  return 1;
}

void Network::clearLists(){
  /*FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_COPY(&this->master,&this->readfds);
  FD_COPY(&this->master,&this->writefds);
  FD_COPY(&this->master,&this->exceptionfds);*/
  this->readfds=this->master;
  this->writefds=this->master;
  this->exceptionfds=this->master;
}

void Network::closeSocket(int socketNumber){
  shutdown(socketNumber, SHUT_RDWR);
  close(socketNumber);
  clearSocket(socketNumber);
  updateFdmax();
}

void Network::selectDescriptor(){
  clearLists();
  if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, NULL) == -1){
    perror("Cannot select descriptor");
    return;
  }
  else{
    for(int socketNumber=0;socketNumber<this->sockets;socketNumber++){
      if(FD_ISSET(this->activeSockets[socketNumber] , &this->readfds)){
        //NOWE POŁĄCZENIE
        if(this->activeSockets[socketNumber] == this->server.getSocketNumber()) connectClient();
        else {}//ODBIÓR WIADOMOSCI
      }
      if(FD_ISSET(this->activeSockets[socketNumber] , &this->writefds)){
        //pisz;
      }
      if(FD_ISSET(this->activeSockets[socketNumber] , &this->exceptionfds)){
        //sygnał;
      }
    }
  }
}

void Network::connectClient(){
  int fdnumber = this->server.acceptConnection();
  if(fdnumber==-1) return;
  Client NewClient(fdnumber);
  addSocket(fdnumber);
  this->activeClients.push_back(NewClient);
}

int Network::setMessage(string message,int size, string client){
  // MUTEX.WAIT if message is set
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == client){
      this->activeClients[i].setNewMessage(message,size);
      return 1;
    }
    i++;
  }
  return -1;
}

void Network::sendMessage(Client& client){
  if(client.getIsMessageSet() == false) {
    return;
  }
  else if(client.getIsSizeSent() == false){
    int result = client.sendSize();
    if(result == -1); // CLIENT IS OFFLINE
  }
  else{
    int result = client.sendBuffer();
    if(result == -1); // CLIENT IS OFFLINE
    else if(result == 0) return; //full message is not sent yet
    else{
      //wiadomosc wyslana - i tyle
      client.messageSent();
    }
  }
}

void Network::receiveMessage(Client& client){
  if(client.getIsSizeReceived() == false){
    int result = client.receiveSize();
    if(result == -1); //CLIENT IS OFFLINE
    else if(result == 0); // sth gone wrong - repeat
    else return; //everything is perfect
  }
  else{
    int result = client.receiveBuffer();
    if(result == -1); //CLIENT IS OFFLINE
    else if(result == 0) return; //full message is not received yet
    else{
      //wiadomosc odebrania daj znac transport
      this->transport.receiveAndParse(client.getReceivingBuffer());
      //i wyczysc wiadomosci
      client.messageReceived();
    }
  }
}