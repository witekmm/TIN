#include "DataBaseConnector.h"

DataBaseConnector::DataBaseConnector(std::shared_ptr<ClientSessionPipes> clients)
    : database() , Reply(clients){}

void DataBaseConnector::sendGroupMessage(std::string content, std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group doesn't exist");
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    Reply::incorrectMessage(clientId, "You can't send message to group you do not belong");
    return;
  }
  this->database.addMsgToGroup(groupName, login, 1, content);
  Reply::correctMessage(clientId);
  std::vector<Client> loggedclients = Reply::getLoggedClients();
  for(auto it = loggedclients.begin() ; it != loggedclients.end() ; it++){
    if(this->database.belongsToGroup(groupName , it->getLogin())){
      Reply::createAndSetMessage(login , content ,groupName, 1 , it->getLocalId());
    }
  }
}

void DataBaseConnector::createGroup(std::string groupName, std::string login, int clientId)
{
  if(this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group name already in use", groupName, Message::ClientMessage::CREATE);
    return;
  }
  this->database.createGroup(groupName, login);
  Reply::correctMessage(clientId, groupName, Message::ClientMessage::CREATE);
}

void DataBaseConnector::deleteGroup(std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group doesn't exist", groupName, Message::ClientMessage::DELETE);
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectMessage(clientId, "You can't delete group you are not a administrator", groupName, Message::ClientMessage::DELETE);
    return;
  }
  this->database.deleteGroup(groupName);
  Reply::correctMessage(clientId, groupName, Message::ClientMessage::DELETE);
}

void DataBaseConnector::requestToGroup(std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group doesn't exist");
    return;
  }
  if(this->database.belongsToGroup(groupName , login)){
    Reply::incorrectMessage(clientId, "You already belong to choosen group");
    return;
  }
  if((this->database.isMsgOfTypeForGroup(groupName , login , 2)) != -1){
    Reply::incorrectMessage(clientId, "Request from this user already exist");
    return;
  }
  Reply::correctMessage(clientId);
  std::string adminName = this->database.addMsgToAdministrator(groupName, login , 2 , "");
  int adminId = Reply::findClientID(adminName);
  if(adminId == -1) return;
  else Reply::createAndSetMessage(login , "" ,groupName, 2 , adminId);
}

void DataBaseConnector::acceptRequest(std::string groupName, std::string userName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectMessage(clientId, "You have no right to reply for request");
    return;
  }/*
  int msgid = this->database.isMsgOfTypeForGroup(groupName , userName, 2);
  if(msgid == -1){
    Reply::incorrectMessage(clientId, "No request from this user");
    return;
  }*/
  //usun go
  Reply::correctMessage(clientId);
  //this->database.deleteMsgOfTypeForGroup(groupName , userName , 2);
  int msgid = this->database.createMsg(groupName , login , 3 , "");
  std::string user = this->database.addMsgToUser(msgid , this->database.getUserId(userName));
  this->database.addUserToGroup(groupName , userName);
  int userId = Reply::findClientID(user);
  if(userId == -1) return;
  else Reply::createAndSetMessage(login , "" ,groupName, 3 , userId);
}

void DataBaseConnector::declineRequest(std::string groupName, std::string userName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectMessage(clientId, "You have no right to reply for request");
    return;
  }/*
  int msgid = this->database.isMsgOfTypeForGroup(groupName , userName, 2);
  if(msgid == -1){
    Reply::incorrectMessage(clientId, "No request from this user");
    return;
  }*/
  //usun go
  Reply::correctMessage(clientId);
  //this->database.deleteMsgOfTypeForGroup(groupName , userName , 2);
  int msgid = this->database.createMsg(groupName , login , 4 , "");
  std::string user = this->database.addMsgToUser(msgid , this->database.getUserId(userName));
  int userId = Reply::findClientID(user);
  if(userId == -1) return;
  else Reply::createAndSetMessage(login , "" ,groupName, 4 , userId);
}

void DataBaseConnector::leaveGroup(std::string groupName, std::string login, int clientId)
{
  //czy grupa istnieje
  if(!this->database.isGroup(groupName)){
    Reply::incorrectMessage(clientId, "Group doesn't exist", groupName, Message::ClientMessage::LEAVE);
    return;
  }
  //czy nalezy do grupy
  if(!this->database.belongsToGroup(groupName , login)){
    Reply::incorrectMessage(clientId, "You can't leave group you don't belong", groupName, Message::ClientMessage::LEAVE);
    return;
  }
  int id = this->database.getUserId(login);
  if(this->database.isAdministrator(groupName, id)){
    this->database.removeAllUsersFromGroup(groupName);
    this->database.deleteGroup(groupName);
    Reply::correctMessage(clientId, groupName, Message::ClientMessage::LEAVE);
    return;
  }
  this->database.removeUserFromGroup(groupName, login);
  Reply::correctMessage(clientId, groupName, Message::ClientMessage::LEAVE);
}

int DataBaseConnector::logInUser(std::string login, std::string password, int clientId)
{
  //czy uzytkownik istnieje
  if(!this->database.isUser(login)){
    return -1;
  }
  std::string temp = this->database.getUserPassword(login);
  //czy haslo sie zgadza
  if(password!=temp){
    return -2;
  }
  if(Reply::checkIfClientAlreadyLoggedIn(login)){
    Reply::incorrectMessage(clientId , "User already logged");
    return 0;
  }
  //zaloguj
  Reply::logInChoosenUser(clientId, login);
  //wyslij odpowiedz i dolacz wszystkie grupy
  std::vector<int> groups = this->database.getAllGroupsForUser(login);
  std::vector<std::string> groupsByString;
  for(auto it = groups.begin() ; it!=groups.end() ; it++){
    groupsByString.push_back( this->database.getGroupName(*it) );
  }
  Reply::correctLoginMessage(clientId, groupsByString);
  getAllUsersMessagesAndSend(login , clientId);
  return 0;
}

int DataBaseConnector::registerUser(std::string login, std::string password, int clientId)
{
  if(this->database.isUser(login)){
    return -3;
  }
  this->database.addUser(login, password);
  //zaloguj
  Reply::logInChoosenUser(clientId, login);
  Reply::correctMessage(clientId);
  return 0;
}

bool DataBaseConnector::checkIfMessageExistAndSend(std::string login){
  return this->database.hasMsg(login);
}

int DataBaseConnector::rootDeleteGroup(std::string groupName){
  if(!this->database.isGroup(groupName)){
    return -1;
  }
  this->database.deleteGroup(groupName);
  return 0;
}

int DataBaseConnector::rootDeleteUser(std::string login){
  if(!this->database.isUser(login)){
    return -1;
  }
  this->database.deleteUser(login);
  return 0;
}

int DataBaseConnector::rootAddUser(std::string login, std::string password){
  if(this->database.isUser(login)){
    return -1;
  }
  this->database.addUser(login, password);
  return 0;
}

int DataBaseConnector::rootAddGroup(std::string groupName, std::string administrator){
  if(!this->database.isUser(administrator)){
    return -1;
  }
  if(this->database.isGroup(groupName)){
    return -2;
  }
  this->database.createGroup(groupName, administrator);
  return 0;
}

void DataBaseConnector::getAllUsersMessagesAndSend(std::string login, int id){
  std::vector<int> messages = this->database.getAllMsgsForUser(login);
  for(auto it = messages.begin() ; it!= messages.end() ; it++){
    int type = this->database.getMsgType(*it);
    std::string content = this->database.getMsgText(*it);
    std::string sender = this->database.getMsgSender(*it);
    std::string groupName = this->database.getMsgGroupName(*it);
    Reply::createAndSetMessage(sender , content ,groupName, type , id);
  }
}

void DataBaseConnector::deleteLastUserMessage(std::string login){
  int temp = this->database.getOldestMsgForUser(login);
  this->database.deleteOldestMsgForUser(login);
  this->database.removeMsgIfForNoUser(temp);
}
