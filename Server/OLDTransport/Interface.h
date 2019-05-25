#ifndef INTERFACE_H
#define INTERFACE_H
using namespace std;
#include <string>
#include <iostream>
#include <functional>

//#include "../Network/Network.h"
#include "../Logic/HandleMessage.h"

//class Network;

class HandleMessage;

class Interface{
  bool working;
  //Network& network;
  HandleMessage& handleMessage;
public:
  Interface();
  void mainCommand();
  int getNumber();
  string getString();
  int getStringAndEncode();
  void clearInput();
  void closeInterface();
  void setHandleMessage(HandleMessage& handleMessage);
};

#endif
