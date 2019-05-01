#include "HandleMessage.h"
#include "../Transport/Transport.h"
#include "HandleDataBase.h"

void HandleMessage::checkReceivedMessage(Message::ClientMessage message, string login,int socketNumber){
  if(!message.has_messagetype()){
    perror("Message is incorrect!");
    return;
  }

  if(message.messagetype() == Message::ClientMessage::GROUP){
    groupHandle(message,login);
  }
  else if(message.messagetype() == Message::ClientMessage::COMMAND){
    commandHandle(message,login);
  }
  else if(message.messagetype() == Message::ClientMessage::AUTHORIZATION){
    authorizationHandle(message,login,socketNumber);
  }
}

void HandleMessage::groupHandle(Message::ClientMessage message, string login){
  if(!message.has_groupactiontype()){
    perror("Message is incorrect!");
    return;
  }

  if(message.groupactiontype() == Message::ClientMessage::MESSAGE){
    this->database.sendGroupMessage(message.messagecontent() , message.groupname() , login);
  }
  else if(message.groupactiontype() == Message::ClientMessage::CREATE){
    this->database.createGroup(message.groupname() , login);
  }
  else if(message.groupactiontype() == Message::ClientMessage::DELETE){
    this->database.deleteGroup(message.groupname() , login);
  }
  else if(message.groupactiontype() == Message::ClientMessage::REQUEST){
    this->database.requestToGroup(message.groupname() , login);
  }
  else if(message.groupactiontype() == Message::ClientMessage::ACCEPT){
    this->database.acceptRequest(message.groupname() , message.username() , login);
  }
  else if(message.groupactiontype() == Message::ClientMessage::DECLINE){
    this->database.declineRequest(message.groupname() , message.username() , login);
  }
  else if(message.groupactiontype() == Message::ClientMessage::LEAVE){
    this->database.leaveGroup(message.groupname() , login);
  }
}

void HandleMessage::authorizationHandle(Message::ClientMessage message, string login,int socketNumber){
  if(!message.has_authorizationtype()){
    perror("Message is incorrect!");
    return;
  }

  if(message.authorizationtype() == Message::ClientMessage::LOG_IN){
    if(!message.has_login()){
      perror("No login included!");
      return;
    }
    if(!message.has_password()){
      perror("No password included!");
      return;
    }
    this->database.logInUser(message.login() , message.password(),socketNumber);
  }
  else if(message.authorizationtype() == Message::ClientMessage::REGISTER_LOGIN){
    this->database.addLogin(message.login() , socketNumber);
  }
  else if(message.authorizationtype() == Message::ClientMessage::REGISTER_PASSWORD){
    this->database.addPasswordToLogin(message.login() , message.password() , socketNumber);
  }
}

void HandleMessage::commandHandle(Message::ClientMessage message,string login){
  if(!message.has_commandtype()){
    perror("Message is incorrect!");
    return;
  }

  if(message.commandtype() == Message::ClientMessage::EXIT){
    //this->transport.disconnect(login);
  }
  else if(message.commandtype() == Message::ClientMessage::LOG_OUT){
    //this->transport.logOut(login);
  }
}
