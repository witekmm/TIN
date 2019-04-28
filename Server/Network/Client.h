#pragma once
using namespace std;
#include "NetLibs.h"
#include "ClientStatus.h"
#ifndef CLIENT_H
#define CLIENT_H

class Client{
  //buffer for sending
  string sendingBuffer;
  int sendingSize;
  //Info about actual connection
  bool isSizeSent;
  //buffer for sending
  string receivingBuffer;
  int receivingSize;
  //Info about actual connection
  bool isSizeReceived;
  int bytesToReceive;
  //information about client's session
  int socketNumber;
  ClientStatus status;
  string login;

public:
  Client(int socketNumber);
  //get clients login
  string operator*(int);
  int operator==(int toCheck);
  //Sending
  int sendBuffer();
  int receiveBuffer();
  int sendSize();
  int receiveSize();
  //Set new message to send
  void setNewMessage(string content,int bufferSize);
  //session info set
  void setLogin(string login);
  //get
  string getReceivingBuffer();
  int getSocketNumber();
  //clear recv
  void messageReceived();
  //clear send
  void messageSend();
};

#endif
