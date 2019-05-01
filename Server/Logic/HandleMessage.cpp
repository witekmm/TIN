#include "HandleMessage.h"
#include "../Transport/Transport.h"

int HandleMessage::checkReceivedMessage(Message::ClientMessage message, string login,int socketNumber){
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
    authorizationHandle(message,login,socketNumber);
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
    this->database.acceptRequest(message.groupName() , message.userName() , login);
  }
  else if(message.groupActionType() == DECLINE){
    this->database.declineRequest(message.groupName() , message.userName());
  }
  else if(message.groupActionType() == LEAVE){
    this->database.leaveGroup(message.groupName() , login);
  }
}

int HandleMessage::authorizationHandle(Message::ClientMessage message, string login,int socketNumber){
  if(!message.has_authorizationType()){
    perror("Message is incorrect!");
    return 0;
  }

  if(message.authorizationType() == LOG_IN){
    if(!message.has_login()){
      perror("No login included!");
      return 0;
    }
    if(!message.has_password()){
      perror("No password included!");
      return 0;
    }
    this->database.logInUser(message.login() , message.password(),socketNumber);
  }
  else if(message.authorizationType() == REGISTER_LOGIN){
    this->database.addLogin(message.login() , socketNumber);
  }
  else if(message.authorizationType() == REGISTER_PASSWORD){
    this->database.addPasswordToLogin(message.login() , message.password() , socketNumber);
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
