#include "NetLibs.h"
#include "Client.h"

Client::Client(int socketNumber){
  this->socketNumber=socketNumber;
}

Client::~Client(){
  if(this->clientBuffer!=NULL) delete[] this->clientBuffer;
}

int Client::sendMessage(char* buffer, int bufferSize){
  int bytesSent = send(this->socketNumber , buffer , bufferSize , MSG_DONTWAIT);
  if(bytesSent==-1) return -1;
  else return bytesSent;
}

int Client::receiveMessage(int bytes){
  setNewBuffer(bytes);
  int bytesReceived = recv(this->socketNumber,this->clientBuffer,bytes,MSG_DONTWAIT)
  if(bytesReceived==-1) return -1;
  else return bytesReceived;
}

void Client::setNewBuffer(int bufferSize){
  this->clientBuffer == new char[bufferSize];
}

void Client::clearBuffer(){
  delete[] this->clientBuffer;
}

char* Client::getClientBuffer(){
  return this->clientBuffer;
}

int getSocketNumber(){
  return this->socketNumber;
}
