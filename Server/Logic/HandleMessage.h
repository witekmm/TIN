#ifndef HANDLE_MESSAGE_H
#define HANDLE_MESSAGE_H

#include <string>
#include <stdio.h>

#include "../../Messages/Message.pb.h"
#include "../Transport/Transport.h"
#include "HandleDataBase.h"

class Transport;

class HandleDataBase;

class HandleMessage{
  Transport& transport;
  HandleDataBase& database;
public:
  void checkReceivedMessage(Message::ClientMessage message, string login,int socketNumber);
  void authorizationHandle(Message::ClientMessage message,string login,int socketNumber);
  void commandHandle(Message::ClientMessage message,string login);
  void groupHandle(Message::ClientMessage message,string login);
};

#endif
