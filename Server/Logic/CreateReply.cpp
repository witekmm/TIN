#include "../../Messages/Message.pb.h"
#include "../Transport/Transport.h"
#include "CreateReply.h"

void CreateReply::userNotInGroup(string groupName,string login){
  string content = "You don't belong to this group!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}

void CreateReply::groupMessageConfirmation(string groupName,string login){
  string content = "Message has been sent!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::MESSAGE);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::groupNameExist(string groupName,string login){
  string content = "Group with selected name already exists!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::CREATE);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::groupCreated(string groupName,string login){
  string content = "Group has been created!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::CREATE);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::groupDoesntExist(string groupName,string login){
  string content = "Group with this name doesn't exist!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::noRightsToDeleteGroup(string groupName,string login){
  string content = "You aren't administrator of the group!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::DELETE);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::groupDeleted(string groupName,string login){
  string content = "Group has been deleted!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::DELETE);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::requestSend(string groupName,string login){
  string content = "Request has been sent!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::REQUEST);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::noRightsToReplyRequest(string groupName,string login){
  string content = "You have no rights to reply to the request!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::NoRequestFromThisPerson(string userName,string login){
  string content = "Request from choosen person doesn't exists!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_username(userName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::requestAccepted(string groupName,string userName,string login){
  string content = "Request has been accepted!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::ACCEPT);
  message.set_groupname(groupName);
  message.set_username(userName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
  // NOW MESSAGE TO USER REQUESTING
  /*string content = "Your request has been accepted!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::REQUEST);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , userName);*/
}
void CreateReply::requestDeclined(string groupName,string userName,string login){
  string content = "Request has been declined!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::DECLINE);
  message.set_groupname(groupName);
  message.set_username(userName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
  // NOW MESSAGE TO USER REQUESTING
  /*string content = "Your request has been declined!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::REQUEST);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , userName);*/
}
void CreateReply::userLeftGroup(string groupName,string login){
  string content = "You left the group!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::LEAVE);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
void CreateReply::newAdmin(string groupName,string newAdmin){
  string content = "You are new administrator of the group!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , newAdmin);
}
void CreateReply::incorrectData(string login,int socketNumber){
  string content = "Incorrect login details!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::AUTHORIZATION);
  message.set_authorizationtype(Message::ClientMessage::LOG_IN);
  message.set_login(login);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , socketNumber);
}
void CreateReply::userLogged(string login,int socketNumber){
  string content = "You have been logged in!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::AUTHORIZATION);
  message.set_authorizationtype(Message::ClientMessage::LOG_IN);
  message.set_login(login);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , socketNumber);
  //LOGOWANIE
  transport.getNetwork().logInClient(socketNumber,login);
}
void CreateReply::loginIsForbidden(string login,int socketNumber){
  string content = "Choosen login already exists!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::AUTHORIZATION);
  message.set_authorizationtype(Message::ClientMessage::REGISTER_LOGIN);
  message.set_login(login);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , socketNumber);
}
void CreateReply::loginIsAvailable(string login,int socketNumber){
  string content = "Choosen login is available!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::AUTHORIZATION);
  message.set_authorizationtype(Message::ClientMessage::REGISTER_LOGIN);
  message.set_login(login);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , socketNumber);
}
void CreateReply::userAccountCreated(string login,int socketNumber){
  string content = "You have been registered!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::AUTHORIZATION);
  message.set_authorizationtype(Message::ClientMessage::REGISTER_PASSWORD);
  message.set_login(login);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , socketNumber);
  //LOGOWANIE
  transport.getNetwork().logInClient(socketNumber,login);
}
void CreateReply::userAlreadyInGroup(string groupName,string login){
  string content = "You already belong to this group!";
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  message.set_groupactiontype(Message::ClientMessage::REQUEST);
  message.set_groupname(groupName);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(content);
  transport.serializeAndSend(message , login);
}
