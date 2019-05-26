#ifndef DATA_BASE_CONNECTOR_H
#define DATA_BASE_CONNECTOR_H

#include "../Database/Database.h"
#include "../ClientSession/ClientSessionPipes.h"
#include "RepliesCreator.h"
#include <memory>
#include <string>
#include <vector>

class DataBaseConnector: public Reply{
  Database database;
public:
  DataBaseConnector(std::shared_ptr<ClientSessionPipes> clients);
  void sendGroupMessage(std::string content, std::string groupName, std::string login);
  void createGroup(std::string groupName, std::string login);
  void deleteGroup(std::string groupName, std::string login);
  void requestToGroup(std::string groupName, std::string login);
  void acceptRequest(std::string groupName, std::string userName, std::string login);
  void declineRequest(std::string groupName, std::string userName, std::string login);
  void leaveGroup(std::string groupName, std::string login);
  int logInUser(std::string login, std::string password);
  int registerUser(std::string login, std::string password);

  bool checkIfMessageExistAndSend(std::string login);

  int rootDeleteGroup(std::string groupName);
  int rootDeleteUser(std::string login);
  int rootAddUser(std::string login, std::string password);
  int rootAddGroup(std::string groupName, std::string administrator);
};

#endif
