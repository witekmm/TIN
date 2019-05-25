#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <cstddef>
#include "../../Messages/Message.pb.h"
#include "DataBaseConnector.h"

class MessageHandler: private DataBaseConnector{
public:
  //There have to be function that monitors users buffers
  //will be there
  //check message type
  int HandleMessage(Message::ClientMessage message, int clientId);
  //check action type
  int HandleAuthorizationType(Message::ClientMessage message);
  int HandleGroupType(Message::ClientMessage message);
  //CLICommandHandler
  //will be there
};

#endif
