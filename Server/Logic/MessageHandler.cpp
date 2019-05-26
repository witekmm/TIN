#include "MessageHandler.h"
#include "../../Messages/Message.pb.h"

MessageHandler::MessageHandler(std::shared_ptr<ClientSessionPipes> clients):
 DataBaseConnector(clients) , clients(clients), working(true){}

void MessageHandler::LogicThreadLoop(){
  while(this->working){
    std::pair<Client, Message::ClientMessage> result = this->clients->writeMessage();

  }
}

int MessageHandler::HandleMessage(Message::ClientMessage message, int clientId){
  if(!message.messagetype()){
    return 1;
  }
  if(message.messagetype() == Message::ClientMessage::GROUP){
      //Sprawdzam czy zalogowany
    return HandleGroupType(message, clientId);
  }
  else if(message.messagetype() == Message::ClientMessage::AUTHORIZATION){

    return HandleAuthorizationType(message);
  }
  /*else if(message.messagetype() == Message::ClientMessage::REPLY){

  }*/
}


int MessageHandler::HandleAuthorizationType(Message::ClientMessage message){
  if(!message.authorizationtype()){
    return 2;
  }
  if(message.login().empty() || message.password().empty()){
    return 3;
  }
  if(message.authorizationtype() == Message::ClientMessage::LOG_IN){
    return DataBaseConnector::logInUser(message.login() , message.password());

  }
  else if(message.authorizationtype() == Message::ClientMessage::REGISTER){
    return DataBaseConnector::registerUser(message.login() , message.password());
  }
}


int MessageHandler::HandleGroupType(Message::ClientMessage message, int clientId){
  if(!message.groupactiontype()){
    return 2;
  }
  std::string login;
  //login = this->clients->getUserLogin(clientId);
  if(message.groupactiontype() == Message::ClientMessage::MESSAGE){
    if(message.messagecontent().empty() || message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::sendGroupMessage(message.messagecontent() , message.groupname() , login);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::CREATE){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::createGroup( message.groupname() , login);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DELETE){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::deleteGroup( message.groupname() , login);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::REQUEST){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::requestToGroup( message.groupname() , login);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::ACCEPT){
    if(message.groupname().empty() || message.username().empty()){
      return 3;
    }
    DataBaseConnector::acceptRequest( message.groupname(), message.username() , login);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DECLINE){
    if(message.groupname().empty() || message.username().empty()){
      return 3;
    }
    DataBaseConnector::declineRequest( message.groupname(), message.username() , login);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::LEAVE){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::leaveGroup( message.groupname() , login);
    return 0;
  }
}
