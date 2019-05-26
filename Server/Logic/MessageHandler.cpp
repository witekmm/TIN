#include "MessageHandler.h"
#include "../../Messages/Message.pb.h"

MessageHandler::MessageHandler(std::shared_ptr<ClientSessionPipes> clients):
 DataBaseConnector(clients) , clients(clients), working(true){}

void MessageHandler::LogicThreadLoop(){
  while(this->working){
    std::pair<Client, Message::ClientMessage> result = this->clients->writeMessage();
    int res = HandleMessage(result.second , result.first.getLocalId() , result.first.getLogin() , result.first.isLogged());
    switch (res)
    {
      case -3:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "Login doesn't exist!");
        break;
      case -2:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "Wrong password!");
        break;
      case -1:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "Login doesn't exist!");
        break;
      case 0:
        break;
      case 1:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "No message type!");
        break;
      case 2:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "No action type!");
        break;
      case 3:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "Missing pools!");
        break;
      case 4:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "Not logged in!");
        break;
      case 5:
        DataBaseConnector::Reply::incorrectAuthorizationTypeMessage(result.first.getLocalId() , "Already logged in!");
        break;
    }
  }
}

void MessageHandler::DataBaseMessageCheckLoop(){
  while(this->working){
    std::vector<Client> users = this->clients->getLoggedClients();
    for(auto it = users.begin() ; it != users.end() ; it++){
      //Client temp = *it;
      DataBaseConnector::getAllUsersMessagesAndSend( it->getLogin() , it->getLocalId() );
    }
  }
}

int MessageHandler::HandleMessage(Message::ClientMessage message, int clientId, std::string clientlogin,bool islogged){
  if(!message.messagetype()){
    return 1;
  }
  if(message.messagetype() == Message::ClientMessage::GROUP){
    if(!islogged) return 4;
    return HandleGroupType(message, clientlogin, clientId);
  }
  else if(message.messagetype() == Message::ClientMessage::AUTHORIZATION){
    if(islogged) return 5;
    return HandleAuthorizationType(message, clientId);
  }
  else if(message.messagetype() == Message::ClientMessage::REPLY){
    if(!islogged) return 4;
    DataBaseConnector::deleteLastUserMessage(clientlogin);
    return 0;
  }
}


int MessageHandler::HandleAuthorizationType(Message::ClientMessage message, int clientId){
  if(!message.authorizationtype()){
    return 2;
  }
  if(message.login().empty() || message.password().empty()){
    return 3;
  }
  if(message.authorizationtype() == Message::ClientMessage::LOG_IN){
    return DataBaseConnector::logInUser(message.login() , message.password(), clientId);

  }
  else if(message.authorizationtype() == Message::ClientMessage::REGISTER){
    return DataBaseConnector::registerUser(message.login() , message.password() , clientId);
  }
}


int MessageHandler::HandleGroupType(Message::ClientMessage message, std::string login, int clientId){
  if(!message.groupactiontype()){
    return 2;
  }
  if(message.groupactiontype() == Message::ClientMessage::MESSAGE){
    if(message.messagecontent().empty() || message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::sendGroupMessage(message.messagecontent() , message.groupname() , login, clientId);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::CREATE){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::createGroup( message.groupname() , login, clientId);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DELETE){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::deleteGroup( message.groupname() , login, clientId);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::REQUEST){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::requestToGroup( message.groupname() , login, clientId);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::ACCEPT){
    if(message.groupname().empty() || message.username().empty()){
      return 3;
    }
    DataBaseConnector::acceptRequest( message.groupname(), message.username() , login, clientId);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::DECLINE){
    if(message.groupname().empty() || message.username().empty()){
      return 3;
    }
    DataBaseConnector::declineRequest( message.groupname(), message.username() , login, clientId);
    return 0;
  }
  else if(message.groupactiontype() == Message::ClientMessage::LEAVE){
    if(message.groupname().empty()){
      return 3;
    }
    DataBaseConnector::leaveGroup( message.groupname() , login , clientId);
    return 0;
  }
}
