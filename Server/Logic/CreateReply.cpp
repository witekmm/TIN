#include "../../Messages/Message.pb.h"
#include "../Transport/Transport.h"
#include "CreateReply.h"

void CreateReply::userNotInGroup(string groupName,string login){
  string content = "You don't belong to this group!";
  Message::ClientMessage message();
  message.set_messageType(Message::ClientMessage::GROUP);
  message.set_groupName(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replyContent(content);
  transport.serializeAndSend(message,login);
}

void CreateReply::groupMessageConfirmation(string groupName,string login);
void CreateReply::groupNameExist(string groupName,string login);
void CreateReply::groupCreated(string groupName,string login);
void CreateReply::groupDoesntExist(string groupName,string login);
void CreateReply::noRightsToDeleteGroup(string groupName,string login);
void CreateReply::groupDeleted(string groupName,string login);
void CreateReply::requestSend(string groupName,string login);
void CreateReply::noRightsToReplyRequest(string groupName,string login);
void CreateReply::NoRequestFromThisPerson(string userName,string login);
void CreateReply::requestAccepted(string groupName,string userName,string login);
void CreateReply::requestDeclined(string groupName,string userName,string login);
void CreateReply::userLeftGroup(string groupName,string login);
void CreateReply::newAdmin(string groupName,string newAdmin);
void CreateReply::incorrectData(string login,int socketNumber);
void CreateReply::userLogged(string login,int socketNumber);
void CreateReply::loginIsForbidden(string login,int socketNumber);
void CreateReply::loginIsAvailable(string login,int socketNumber);
void CreateReply::userAccountCreated(string login,int socketNumber);
void CreateReply::userAlreadyInGroup(string groupName,string login);
