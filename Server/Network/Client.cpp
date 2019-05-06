using namespace std;
#include <string.h>
#include "NetLibs.h"
#include "Client.h"

Client::Client(int socketNumber){
  this->socketNumber=socketNumber;
  this->status=unauthorized;
  this->login="unauthorized";
  pthread_cond_init(&this->cond, NULL);
  messageReceived();
  messageSent();
}

Client::Client(){
  this->login="unauthorized";
  this->status=unauthorized;
  messageReceived();
  messageSent();
}
/*
string Client::operator*(int){
  return this->login;
}
*/
int Client::operator==(int toCheck){
  if(this->socketNumber==toCheck) return 1;
  else return 0;
}

int Client::operator==(string toCheck){
  if(this->login == toCheck) return 1;
  else return 0;
}

int Client::sendBuffer(){
  const char* temp=this->sendingBuffer.c_str();
  int bytesSent = send(this->socketNumber , temp, this->sendingSize , MSG_DONTWAIT);
  if(bytesSent==-1){
    return -1;
  }
  else if(bytesSent < this->sendingSize){
    this->sendingBuffer.erase(0,bytesSent);
    this->sendingSize-=bytesSent;
    return 0;
  }
  else{
    this->sendingSize=0;
    this->sendingBuffer.clear();
    return 1;
  }
}

int Client::sendSize(){
  char* temp = new char[4];
  memcpy(temp , (char*)&this->sendingSize , 4);
  int bytesSent = send(this->socketNumber , temp , 4 , MSG_DONTWAIT);
  if(bytesSent == -1){
    return -1;
  }
  else if(bytesSent!=4){
    return 0;
  }
  else{
    this->isSizeSent=true;
    return 1;
  }
}

int Client::receiveBuffer(){
  char temp[bytesToReceive];
  int bytesReceived = recv(this->socketNumber, &temp, this->bytesToReceive , MSG_DONTWAIT );
  string tempBuffer(temp);
  if(bytesReceived == -1){
    return -1;
  }
  else if(bytesReceived < this->bytesToReceive){
    this->receivingBuffer+=tempBuffer;
    this->bytesToReceive-=bytesReceived;
    return 0;
  }
  else{
    this->receivingBuffer+=tempBuffer;
    this->bytesToReceive=0;
    return 1;
  }
}

int Client::receiveSize(){
  char temp[bytesToReceive];
  int bytesReceived = recv(this->socketNumber, &temp, 4 , MSG_DONTWAIT );
  int rec=atoi(temp);
  if(bytesReceived == -1){
    return -1;
  }
  else if(bytesReceived!=4){
    return 0;
  }
  else{
    this->isSizeReceived=true;
    this->bytesToReceive=rec;
    return 1;
  }
}

void Client::setNewMessage(string content,int bufferSize){
  pthread_mutex_lock(&this->mutex);
  do {
  	if (this->isMessageSet==0) {
      this->sendingBuffer = content;
      this->sendingSize = bufferSize;
      this->isMessageSet = true;
  		break;
  	}
  	else
  		pthread_cond_wait(&this->cond, &this->mutex);
  } while (1);
  pthread_mutex_unlock(&this->mutex);
  }

void Client::setLogin(string login){
  this->login=login;
}

string &Client::getReceivingBuffer(){
  string& temp(this->receivingBuffer);
  return temp;
}

int Client::getSocketNumber(){
  return this->socketNumber;
}

void Client::messageReceived(){
  this->isSizeReceived=false;
  this->bytesToReceive=0;
  this->receivingBuffer.clear();
}

void Client::messageSent(){
  pthread_mutex_lock(&this->mutex);
  this->sendingSize=0;
  this->isSizeSent=false;
  this->isMessageSet=false;
  this->sendingBuffer.clear();
  pthread_cond_signal(&this->cond);
  pthread_mutex_unlock(&this->mutex);
}

bool Client::getIsMessageSet(){
  return this->isMessageSet;
}

bool Client::getIsSizeSent(){
  return this->isSizeSent;
}

bool Client::getIsSizeReceived(){
  return this->isSizeReceived;
}

string Client::getLogin(){
  return this->login;
}

void Client::authorize(){
  if(this->status!=unauthorized) return;
  this->status=authorized;
}

void Client::logIn(){
  if(this->status==logged) return;
  this->status=authorized;
}

void Client::logOut(){
  if(this->status!=logged) return;
  this->status=unauthorized;
}

int Client::isLogged(){
  if(this->status==logged) return 1;
  return 0;
}
