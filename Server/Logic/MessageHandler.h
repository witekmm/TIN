#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <memory>
#include <utility>
#include <vector>

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
  void DataBaseMessageCheckLoop();

  int HandleMessage(Message::ClientMessage message, int clientId, std::string clientlogin,bool islogged);
  //check action type
  int HandleAuthorizationType(Message::ClientMessage message, int clientId);
  int HandleGroupType(Message::ClientMessage message, std::string login, int clientId);
  //CLICommandHandler
  //will be there
};

#endif
