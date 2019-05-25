#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include "../../Messages/Message.pb.h"

class MessageHandler{
public:
  //There have to be function that monitors users buffers
  //will be there
  //check message type
  int HandleMessage(Message::ClientMessage message, int clientId);
  //check action type
  int HandleAuthorizationType(Message::ClientMessage message, int clientId);
  int HandleGroupType(Message::ClientMessage message, int clientId);
  //CLICommandHandler
  //will be there
};

#endif
