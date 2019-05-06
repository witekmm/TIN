#ifndef HANDLE_DATA_BASE_H
#define HANDLE_DATA_BASE_H

using namespace std;
#include "CreateReply.h"

//#include <mysql.h>
#include <string>

class HandleDataBase{
  CreateReply createReply;
public:
  HandleDataBase(CreateReply& cr);
  void sendGroupMessage(string content , string groupName , string login);
  void createGroup(string groupName , string login);
  void deleteGroup(string groupName , string login);
  void requestToGroup(string groupName , string login);
  void acceptRequest(string groupName , string userName ,string login);
  void declineRequest(string groupName , string userName ,string login);
  void leaveGroup(string groupName , string login);
  void logInUser(string login, string password, int socketNumber);
  void addLogin(string login, int socketNumber);
  void addPasswordToLogin(string login, string password, int socketNumber);

  void checkIfMessageExistAndSend(string login);

  int rootDeleteGroup(string groupName);
  int rootDeleteUser(string login);
  int rootAddUser(string login, int password);
  int rootAddGroup(string groupName, string administrator);

};

#endif
