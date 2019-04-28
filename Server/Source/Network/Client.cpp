using namespace std;
#include "NetLibs.h"
#include "Client.h"

Client::Client(int socketNumber){
  this->socketNumber=socketNumber;
  this->status=unauthorized;
}

Client::~Client(){
  if(this->clientBuffer!=nullptr) delete[] this->clientBuffer;
}

int Client::operator*(int){
  return this->socketNumber;
}

int Client::operator==(int toCheck){
  if(this->socketNumber==toCheck) return 1;
  else return 0;
}

int Client::sendMessage(char* buffer, int bufferSize){
  int bytesSent = send(this->socketNumber , buffer , bufferSize , MSG_DONTWAIT);
  if(bytesSent==-1) return -1;
  else return bytesSent;
}

int Client::receiveMessage(int bytes){
  setNewBuffer(bytes);
  int bytesReceived = recv(this->socketNumber,this->clientBuffer,bytes,MSG_DONTWAIT);
  if(bytesReceived==-1) return -1;
  else return bytesReceived;
}

void Client::setNewBuffer(int bufferSize){
  this->clientBuffer == new char[bufferSize];
}

void Client::setLogin(string login){
  this->login=login;
}

void Client::clearBuffer(){
  delete[] this->clientBuffer;
}

char* Client::getClientBuffer(){
  return this->clientBuffer;
}

int Client::getSocketNumber(){
  return this->socketNumber;
}
