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
  void incorrectMessage(int clientId, std::string error);
  void incorrectMessage(int clientId, std::string error, std::string groupName,Message::ClientMessage_groupActionTypes type);
  void correctMessage(int clientId);
  void correctMessage(int clientId, std::string groupName,Message::ClientMessage_groupActionTypes type);

  void correctLoginMessage(int clientId, std::vector<std::string> groups);

  void createAndSetMessage(std::string sender, std::string content, std::string groupName,int type , int clientId);
  void logInChoosenUser(int clientId, std::string login);

  std::vector<Client> getLoggedClients();
  int findClientID(std::string login);
  bool checkIfClientAlreadyLoggedIn(std::string login);
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
