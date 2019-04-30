#include "HandleMessage.h"
#include "../Transport/Transport.h"

void HandleMessage::checkReceivedMessage(Message::ClientMessage message, string login){
  if(!message.has_messageType()){
    perror("Message is incorrect!");
    return;
  }

  if(message.messageType() == GROUP){
    groupHandle(message,login);
  }
  else if(message.messageType() == COMMAND){
    commandHandle(message,login);
  }
  else if(message.messageType() == AUTHORIZATION){
    authorizationHandle(message,login);
  }
}

void HandleMessage::groupHandle(Message::ClientMessage message, string login){
  if(!message.has_groupActionType()){
    perror("Message is incorrect!");
    return;
  }

  if(message.groupActionType() == MESSAGE){
    this->database.sendGroupMessage(message.messageContent() , message.groupName() , login);
  }
  else if(message.groupActionType() == CREATE){
    this->database.createGroup(message.groupName() , login);
  }
  else if(message.groupActionType() == DELETE){
    this->database.deleteGroup(message.groupName() , login);
  }
  else if(message.groupActionType() == REQUEST){
    this->database.requestToGroup(message.groupName() , login);
  }
  else if(message.groupActionType() == ACCEPT){
    this->database.acceptRequest(message.groupName() , message.userName());
  }
  else if(message.groupActionType() == DECLINE){
    this->database.declineRequest(message.groupName() , message.userName());
  }
  else if(message.groupActionType() == LEAVE){
    this->database.leaveGroup(message.groupName() , login);
  }
}

void HandleMessage::authorizationHandle(Message::ClientMessage message, string login){
  if(!message.has_authorizationType()){
    perror("Message is incorrect!");
    return;
  }

  if(message.authorizationType() == LOGIN){
    this->database.checkUserLogin(message.login());
  }
  else if(message.authorizationType() == PASSWORD){
    this->database.checkUserPassword(message.password() , login);
  }
  else if(message.authorizationType() == BOTH){
    this->database.logInUser(message.login() , message.password());
  }
}

void HandleMessage::commandHandle(Message::ClientMessage message,string login){
  if(!message.has_commandType()){
    perror("Message is incorrect!");
    return;
  }

  if(message.commandType() == EXIT){
    this->transport.disconnect(login);
  }
  else if(message.commandType() == LOG_OUT){
    this->transport.logOut(login);
  }
}
