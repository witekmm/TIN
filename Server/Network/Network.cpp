#include "NetLibs.h"

#include <stdio.h>
#include "Network.h"
#include "../Transport/Transport.h"
using namespace std;
Network::Network(Transport& tp):transport(tp), server(){
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  this->working=true;
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
  if(select(this->fdmax+1, &this->readfds, &this->writefds, &this->exceptionfds, &this->tv) == -1){
    perror("Cannot select descriptor");
    return;
  }
  else{
    for(int i=0 ; i<this->sockets ; i++){
      if(FD_ISSET(this->activeSockets[i] , &this->readfds)){
        //NOWE POŁĄCZENIE
        if(this->activeSockets[i] == this->server.getSocketNumber()){
          thread accept (&Network::connectClient , this);
        }
        else {
          Client& temp = findClient( this->activeSockets[i] );
          thread read (&Network::receiveMessage , this , std::ref(temp) );
          //thread read (&Network::receiveMessage , this , findClient(this->activeSockets[i]) );
        }//ODBIÓR WIADOMOSCI
      }
      if(FD_ISSET(this->activeSockets[i] , &this->writefds)){
        Client& temp = findClient( this->activeSockets[i] );
        thread write (&Network::sendMessage , this , std::ref(temp) );
      }
      if(FD_ISSET(this->activeSockets[i] , &this->exceptionfds)){
        int x = this->activeSockets[i];
        thread disconnect (&Network::disconnectClientBySN , this , x);
        //thread disconnect (disconnectClient , x);
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

int Network::setMessage(string message,int size, int socketNumber){
  // MUTEX.WAIT if message is set
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
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
      this->transport.receiveAndParse(client.getReceivingBuffer() , client.getLogin() , client.getSocketNumber() );
      //i wyczysc wiadomosci
      client.messageReceived();
    }
  }
}


void Network::logInClient(int socketNumber, string login){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      this->activeClients[i].logIn();
      this->activeClients[i].setLogin(login);
      return;
    }
    i++;
  }
}

void Network::authorizeClient(int socketNumber, string login){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      this->activeClients[i].authorize();
      this->activeClients[i].setLogin(login);
      return;
    }
    i++;
  }
}

void Network::logOutClient(string login){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == login){
      this->activeClients[i].logOut();
      return;
    }
    i++;
  }
}

void Network::disconnectClient(string login){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == login){
      int socketNumber = this->activeClients[i].getSocketNumber();
      closeSocket(socketNumber);
      clearSocket(socketNumber);
      return;
    }
    i++;
  }
}

void Network::disconnectClientBySN(int socketNumber){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == i){
      int socketNumber = this->activeClients[i].getSocketNumber();
      closeSocket(socketNumber);
      clearSocket(socketNumber);
      return;
    }
    i++;
  }
}

int Network::isClientLogged(int socketNumber){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      return this->activeClients[i].isLogged();
    }
    i++;
  }
}

Client& Network::findClient(int socketNumber){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      return this->activeClients.at(i);
    }
    i++;
  }
}

int Network::checkIfClient(string login){
  vector<Client>::iterator it = this->activeClients.begin();
  for(it ; it != this->activeClients.end(); it++){
    if(*it == login){
      return 1;
    }
  }
  return 0;
}

int Network::checkIfClient(int socketNumber){
  vector<Client>::iterator it = this->activeClients.begin();
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      return 1;
    }
  }
  return 0;
}

int Network::checkIfClientOccupied(int socketNumber){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == socketNumber){
      return this->activeClients[i].getIsMessageSet();
    }
    i++;
  }
  return -1;
}

int Network::checkIfClientOccupied(string login){
  vector<Client>::iterator it = this->activeClients.begin();
  int i=0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == login){
      return this->activeClients[i].getIsMessageSet();
    }
    i++;
  }
  return -1;
}

vector<pair<string , int>> Network::getClientsList(){
  vector<pair<string , int>> list;
  pair<string , int> apair;
  for(int i=0 ; i < this->sockets-1 ; i++){
    apair.first = this->activeClients[i].getLogin();
    apair.second = this->activeClients[i].getSocketNumber();
    list.push_back(apair);
  }
  return list;
}

void Network::checkClientsMessagesLoop(){
  while(this->working){
    for(int i = 0; i < this->sockets-1 ; i++){
      if(!this->activeClients[i].getIsMessageSet() && this->activeClients[i].isLogged()){
        //daj sygnal HandleMessage zeby wyslal wiadomosc jesli istnieje taka w bazie danych
      }
    }
  }
}
