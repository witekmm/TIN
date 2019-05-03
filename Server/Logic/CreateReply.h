#ifndef CREATE_REPLY_H
#define CREATE_REPLY_H
using namespace std;
#include "../../Messages/Message.pb.h"
#include "../Transport/Transport.h"

#include <string>

class Transport;

class CreateReply{
  Transport& transport;
public:
  void userNotInGroup(string groupName,string login);
  void groupMessageConfirmation(string groupName,string login);
  void groupNameExist(string groupName,string login);
  void groupCreated(string groupName,string login);
  void groupDoesntExist(string groupName,string login);
  void noRightsToDeleteGroup(string groupName,string login);
  void groupDeleted(string groupName,string login);
  void requestSend(string groupName,string login);
  void noRightsToReplyRequest(string groupName,string login);
  void NoRequestFromThisPerson(string userName,string login);
  void requestAccepted(string groupName,string userName,string login);
  void requestDeclined(string groupName,string userName,string login);
  void userLeftGroup(string groupName,string login);
  void newAdmin(string groupName,string newAdmin);
  void incorrectData(string login,int socketNumber);
  void userLogged(string login,int socketNumber);
  void loginIsForbidden(string login,int socketNumber);
  void loginIsAvailable(string login,int socketNumber);
  void userAlreadyInGroup(string groupName,string login);
  void userAccountCreated(string login,int socketNumber);
};

#endif
