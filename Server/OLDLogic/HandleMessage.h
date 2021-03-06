#ifndef HANDLE_MESSAGE_H
#define HANDLE_MESSAGE_H

#include <string>
#include <stdio.h>
#include <iostream>

#include "../../Messages/Message.pb.h"
#include "HandleDataBase.h"

class HandleMessage: public HandleDataBase{

public:
  void checkReceivedMessage(Message::ClientMessage message);
  void authorizationHandle(Message::ClientMessage message);
  void commandHandle(Message::ClientMessage message);
  void groupHandle(Message::ClientMessage message);

  void checkCommand(string command);
  void checkIfMessageExistAndSend(string login);
};

#endif
