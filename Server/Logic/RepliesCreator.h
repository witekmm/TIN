#ifndef REPLIES_CREATOR_H
#define REPLIES_CREATOR_H

#include <string>
#include <memory>
#include <vector>

#include "../../Messages/Message.pb.h"
#include "../ClientSession/ClientSessionPipes.h"

class Reply{
  std::shared_ptr<ClientSessionPipes> clients;
public:
  Reply(std::shared_ptr<ClientSessionPipes> clients);
  void incorrectGroupTypeMessage(std::string login, std::string error);
  void incorrectAuthorizationTypeMessage(int clientsId , std::string error);

  void correctMessage(std::string login);

  void correctLoginMessage(std::string login, std::vector<std::string> groups);
  //uywane przez DataBaseConnector
  //void userNotInGroup(std::string groupName, std::string login);
  //void groupNameExist(std::string groupName, std::string login);
  //void groupDoesntExist(std::string groupName, std::string login);
  //void noRightsToDeleteGroup(std::string groupName, std::string login);
  //void noRightsToReplyRequest(std::string groupName, std::string login);
  //void userAlreadyInGroup(std::string groupName, std::string login);
  //void NoRequestFromThisPerson(std::string userName, std::string login);
  //uzywane przez messagehandler
  //void loginNotInUsed(int clientsId);
  //void incorrectPassword(int clientsId);
  //void loginIsForbidden(int clientsId);
};

#endif
