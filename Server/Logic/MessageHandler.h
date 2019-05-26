#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <memory>
#include <utility>

#include "../../Messages/Message.pb.h"
#include "DataBaseConnector.h"
#include "../ClientSession/ClientSessionPipes.h"

class MessageHandler: public DataBaseConnector{
  std::shared_ptr<ClientSessionPipes> clients;
  bool working;
public:
  MessageHandler(std::shared_ptr<ClientSessionPipes> clients);
  //There have to be function that monitors users buffers
  //will be there
  //check message type
  void LogicThreadLoop();

  int HandleMessage(Message::ClientMessage message, int clientId);
  //check action type
  int HandleAuthorizationType(Message::ClientMessage message);
  int HandleGroupType(Message::ClientMessage message, int clientId);
  //CLICommandHandler
  //will be there
};

#endif
