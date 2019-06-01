#include "RepliesCreator.h"

Reply::Reply(std::shared_ptr<ClientSessionPipes> clients): clients(clients) {}

void Reply::incorrectMessage(int clientId, std::string error){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_replycontent(error);
  //wyslij
  std::cout<<error<<std::endl;
  this->clients->readMessage(clientId,message);
}

void Reply::incorrectMessage(int clientId, std::string error, std::string groupName,Message::ClientMessage_groupActionTypes type){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::NEGATIVE);
  message.set_groupactiontype(type);
  message.set_groupname(groupName);
  message.set_replycontent(error);
  //wyslij
  std::cout<<error<<std::endl;
  this->clients->readMessage(clientId,message);
}

void Reply::correctMessage(int clientId){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  puts("CORRECT MESSAGE");
  this->clients->readMessage(clientId,message);
}

void Reply::correctMessage(int clientId, std::string groupName,Message::ClientMessage_groupActionTypes type){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  message.set_groupactiontype(type);
  message.set_groupname(groupName);
  puts("CORRECT MESSAGE");
  this->clients->readMessage(clientId,message);
}

void Reply::correctLoginMessage(int clientId, std::vector<std::string> groups){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::REPLY);
  message.set_reply(Message::ClientMessage::POSITIVE);
  puts("CORRECT LOGIN MESSAGE");
  for(auto it = groups.begin(); it != groups.end() ; it++){
    message.add_groups( *it );
  }
  this->clients->readMessage(clientId,message);
}

void Reply::logInChoosenUser(int clientId, std::string login){
  this->clients->setClientLogin(clientId, login);
}

void Reply::createAndSetMessage(std::string sender, std::string content, std::string groupName, int type, int clientId){
  Message::ClientMessage message;
  message.set_messagetype(Message::ClientMessage::GROUP);
  switch (type){
    case 1:
      message.set_groupactiontype(Message::ClientMessage::MESSAGE);
      message.set_messagecontent(content);
      message.set_username(sender);
      break;
    case 2:
      message.set_groupactiontype(Message::ClientMessage::REQUEST);
      message.set_username(sender);
      break;
    case 3:
      message.set_groupactiontype(Message::ClientMessage::ACCEPT);
      message.set_groupname(groupName);
      break;
    case 4:
      message.set_groupactiontype(Message::ClientMessage::DECLINE);
      message.set_groupname(groupName);
      break;
  }
  this->clients->readMessage(clientId,message);
}

std::vector<Client> Reply::getLoggedClients(){
  return this->clients->getLoggedClients();
}

int Reply::findClientID(std::string login){
  std::vector<Client> temp = getLoggedClients();
  for(auto it = temp.begin() ; it != temp.end() ; it++){
    if(login == it->getLogin()) return it->getLocalId();
  }
  return -1;
}

bool Reply::checkIfClientAlreadyLoggedIn(std::string login){
  std::vector<Client> loggedClients = this->clients->getLoggedClients();
  for(auto it = loggedClients.begin() ; it!= loggedClients.end() ; it++){
    if(it->getLogin() == login) return true;
  }
  return false;
}
