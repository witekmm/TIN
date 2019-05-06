#ifndef HANDLE_MESSAGE_H
#define HANDLE_MESSAGE_H

#include <string>
#include <stdio.h>
#include <iostream>

#include "../../Messages/Message.pb.h"
#include "../Transport/Transport.h"
#include "HandleDataBase.h"
#include "../Transport/Interface.h"

class Transport;

class HandleDataBase;

class Interface;

class HandleMessage{
  Transport& transport;
  HandleDataBase& database;
  Interface& interface;
public:
  HandleMessage(Transport& t, HandleDataBase& hdb, Interface& i);
  void checkReceivedMessage(Message::ClientMessage message, string login,int socketNumber);
  void authorizationHandle(Message::ClientMessage message,string login,int socketNumber);
  void commandHandle(Message::ClientMessage message,string login);
  void groupHandle(Message::ClientMessage message,string login);
  void checkCommand(string command);
  void checkIfMessageExistAndSend(string login);
  void setTransport(Transport &t);
  void setInterface(Interface& i);
  Interface& getInterface();
};

#endif
