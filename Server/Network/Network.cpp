#include <thread>
#include <stdio.h>
#include "NetLibs.h"
#include "Network.h"
#include "../Transport/Transport.h"

using namespace std;

Network::Network(Transport& tp)
  :transport(tp), server()
{
  this->sockets = 0;
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_ZERO(&this->master);
  this->fdmax = 0;
}

int Network::startServer(int maxConnections, int port, string ip)
{
  Server temp(maxConnections, port, ip);
  this->server = temp;
  if(this->server.createServerSocket() == -1) return -1;
  if(this->server.bindServerSocket() == -1) return -1;
  if(this->server.listenServerSocket() == -1) return -1;
  addSocket(server.getSocketNumber());
  return 0;
}

void Network::clearSocket(int socketNumber)
{
  for(vector<int>::iterator it = activeSockets.begin(); it != activeSockets.end(); it++)
  {
    if(*it == socketNumber)
    {
      activeSockets.erase(it);
      break;
    }
  }
  for(vector<Client>::iterator it = activeClients.begin() ; it != activeClients.end(); it++)
  {
    if(*it == socketNumber)
    {
      activeClients.erase(it);
      break;
    }
  }
  sockets--;
  FD_CLR(socketNumber, &master);
}

void Network::addSocket(int socketNumber)
{
  FD_SET(socketNumber, &master);
  activeSockets.push_back(socketNumber);
  sockets++;
  updateFdmax();
}

void Network::updateFdmax()
{
  int max = 0;
  for(int i = 0; i < sockets; i++)
  {
    if(activeSockets[i] > max) 
      max = activeSockets[i];
  }
  fdmax = max;
}

int Network::checkIfSocket(int socketNumber)
{
  for(int i = 0; i < sockets; i++)
  {
    if(socketNumber == activeSockets[i]) 
      return 0;
  }
  return 1;
}

void Network::clearLists()
{
  /*FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptionfds);
  FD_COPY(&this->master,&this->readfds);
  FD_COPY(&this->master,&this->writefds);
  FD_COPY(&this->master,&this->exceptionfds);*/
  this->readfds = this->master;
  this->writefds = this->master;
  this->exceptionfds = this->master;
}

void Network::closeSocket(int socketNumber)
{
  shutdown(socketNumber, SHUT_RDWR);
  close(socketNumber);
  clearSocket(socketNumber);
  updateFdmax();
}

void Network::selectDescriptor()
{
  clearLists();
  if(select(fdmax + 1, &readfds, &writefds, &exceptionfds, NULL) == -1)
  {
    perror("Cannot select descriptor");
    return;
  }
  else
  {
    for(int i=0; i < sockets; i++)
    {
      if(FD_ISSET(activeSockets[i], &readfds))
      {
        //NOWE POŁĄCZENIE
        if(activeSockets[i] == server.getSocketNumber()){
          thread accept (&Network::connectClient, this);
        }
        else{
          Client& temp = findClient(activeSockets[i]);
          thread read(&Network::receiveMessage, this, std::ref(temp));
          //thread read (&Network::receiveMessage , this , findClient(this->activeSockets[i]) );
        }//ODBIÓR WIADOMOSCI
      }
      if(FD_ISSET(activeSockets[i] , &writefds)){
        Client& temp = findClient(activeSockets[i]);
        thread write(&Network::sendMessage, this, std::ref(temp));
      }
      if(FD_ISSET(activeSockets[i], &exceptionfds)){
        int x = activeSockets[i];
        thread disconnect(&Network::disconnectClientBySN, this, x);
        //thread disconnect (disconnectClient , x);
      }
    }
  }
}

void Network::connectClient(){
  int fdnumber = server.acceptConnection();
  if(fdnumber == -1) 
    return;
  Client newClient(fdnumber);
  addSocket(fdnumber);
  activeClients.push_back(newClient);
}

int Network::setMessage(string message, int size, string client){
  // MUTEX.WAIT if message is set
  vector<Client>::iterator it = activeClients.begin();
  int i=0;
  for(it ; it != activeClients.end(); it++){
    if(*it == client){
      activeClients[i].setNewMessage(message,size);
      return 1;
    }
    i++;
  }
  return -1;
}

int Network::setMessage(string message, int size, int socketNumber){
  // MUTEX.WAIT if message is set
  vector<Client>::iterator it = activeClients.begin();
  int i=0;
  for(it ; it != activeClients.end(); it++){
    if(*it == socketNumber){
      activeClients[i].setNewMessage(message,size);
      return 1;
    }
    i++;
  }
  return -1;
}

void Network::sendMessage(Client& client)
{
  if(!client.getIsMessageSet()) {
    return;
  }
  else if(!client.getIsSizeSent()){
    int result = client.sendSize();
    if(result == -1); // CLIENT IS OFFLINE
  }
  else{
    int result = client.sendBuffer();
    if(result == -1); // CLIENT IS OFFLINE
    else if(result == 0)
      return; //full message is not sent yet
    else{
      //wiadomosc wyslana - i tyle
      client.messageSent();
    }
  }
}

void Network::receiveMessage(Client& client)
{
  if(!client.getIsSizeReceived()){
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


void Network::logInClient(int socketNumber, string login)
{
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

void Network::authorizeClient(int socketNumber, string login)
{
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

void Network::logOutClient(string login)
{
  vector<Client>::iterator it = this->activeClients.begin();
  int i = 0;
  for(it ; it != this->activeClients.end(); it++){
    if(*it == login){
      this->activeClients[i].logOut();
      return;
    }
    i++;
  }
}

void Network::disconnectClient(string login)
{
  vector<Client>::iterator it = activeClients.begin();
  int i = 0;
  for(it ; it != activeClients.end(); it++){
    if(*it == login){
      int socketNumber = activeClients[i].getSocketNumber();
      closeSocket(socketNumber);
      clearSocket(socketNumber);
      return;
    }
    i++;
  }
}

void Network::disconnectClientBySN(int socketNumber)
{
  vector<Client>::iterator it = activeClients.begin();
  int i=0;
  for(it ; it != activeClients.end(); it++){
    if(*it == i){
      int socketNumber = activeClients[i].getSocketNumber();
      closeSocket(socketNumber);
      clearSocket(socketNumber);
      return;
    }
    i++;
  }
}

int Network::isClientLogged(int socketNumber){
  vector<Client>::iterator it = this->activeClients.begin();
  int i = 0;
  for( ; it != activeClients.end(); it++){
    if(*it == socketNumber){
      return activeClients[i].isLogged();
    }
    i++;
  }
}

Client& Network::findClient(int socketNumber){
  vector<Client>::iterator it = activeClients.begin();
  int i = 0;
  for( ; it != activeClients.end(); it++){
    if(*it == socketNumber){
      return activeClients.at(i);
    }
    i++;
  }
}

int Network::checkIfClient(string login){
  vector<Client>::iterator it = this->activeClients.begin();
  for(it ; it != activeClients.end(); it++){
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

vector<pair<string, int>> Network::getClientsList(){
  vector<pair<string , int>> list;
  pair<string , int> apair;
  for(int i=0 ; i < this->sockets-1 ; i++){
    apair.first = this->activeClients[i].getLogin();
    apair.second = this->activeClients[i].getSocketNumber();
    list.push_back(apair);
  }
  return list;
}
