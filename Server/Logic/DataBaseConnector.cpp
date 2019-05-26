#include "DataBaseConnector.h"

DataBaseConnector::DataBaseConnector(std::shared_ptr<ClientSessionPipes> clients)
    : database() , Reply(clients){}

void DataBaseConnector::sendGroupMessage(std::string content, std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group doesn't exist");
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    Reply::incorrectGroupTypeMessage(clientId, "You can't send message to group you do not belong");
    return;
  }
  this->database.addMsgToGroup(groupName, login, 1, content);
  Reply::correctMessage(clientId);
}

void DataBaseConnector::createGroup(std::string groupName, std::string login, int clientId)
{
  if(this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group name already in use");
    return;
  }
  this->database.createGroup(groupName, login);
  Reply::correctMessage(clientId);
}

void DataBaseConnector::deleteGroup(std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectGroupTypeMessage(clientId, "You can't delete group you are not a administrator");
    return;
  }
  this->database.deleteGroup(groupName);
  Reply::correctMessage(clientId);
}

void DataBaseConnector::requestToGroup(std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group doesn't exist");
    return;
  }
  if(this->database.belongsToGroup(groupName , login)){
    Reply::incorrectGroupTypeMessage(clientId, "You already belong to choosen group");
    return;
  }
  if((this->database.isMsgOfTypeForGroup(groupName , login , 2)) == -1){
    Reply::incorrectGroupTypeMessage(clientId, "No request from this user");
    return;
  }
  this->database.addMsgToAdministrator(groupName, login , 2 , "");
  Reply::correctMessage(clientId);
}

void DataBaseConnector::acceptRequest(std::string groupName, std::string userName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectGroupTypeMessage(clientId, "You have no right to reply for request");
    return;
  }
  int msgid = this->database.isMsgOfTypeForGroup(groupName , userName, 2);
  if(msgid == -1){
    Reply::incorrectGroupTypeMessage(clientId, "No request from this user");
    return;
  }
  //usun go
  this->database.deleteMsgOfTypeForGroup(groupName , userName , 2);
  msgid = this->database.createMsg(groupName , login , 3 , "");
  this->database.addMsgToUser(msgid , this->database.getUserId(userName));
  this->database.addUserToGroup(groupName , userName);
  Reply::correctMessage(clientId);
}

void DataBaseConnector::declineRequest(std::string groupName, std::string userName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectGroupTypeMessage(clientId, "You have no right to reply for request");
    return;
  }
  int msgid = this->database.isMsgOfTypeForGroup(groupName , userName, 2);
  if(msgid == -1){
    Reply::incorrectGroupTypeMessage(clientId, "No request from this user");
    return;
  }
  //usun go
  this->database.deleteMsgOfTypeForGroup(groupName , userName , 2);
  msgid = this->database.createMsg(groupName , login , 4 , "");
  this->database.addMsgToUser(msgid , this->database.getUserId(userName));
  Reply::correctMessage(clientId);
}

void DataBaseConnector::leaveGroup(std::string groupName, std::string login, int clientId)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(clientId, "Group doesn't exist");
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    Reply::incorrectGroupTypeMessage(clientId, "You can't leave group you don't belong");
    return;
  }
  int id = this->database.getUserId(login);
  if(this->database.isAdministrator(groupName, id)){
    this->database.removeAllUsersFromGroup(groupName);
    this->database.deleteGroup(groupName);
    return;
  }
  this->database.removeUserFromGroup(groupName, login);
  Reply::correctMessage(clientId);
}

int DataBaseConnector::logInUser(std::string login, std::string password, int clientId)
{
  if(!this->database.isUser(login)){
    return -1;
  }
  std::string temp = this->database.getUserPassword(login);
  if(password!=temp){
    return -2;
  }
  //ZALOGUJ
  std::vector<int> groups = this->database.getAllGroupsForUser(login);
  std::vector<std::string> groupsByString;
  for(auto it = groups.begin() ; it!=groups.end() ; it++){
    groupsByString.push_back( this->database.getGroupName(*it) );
  }
  Reply::correctLoginMessage(clientId, groupsByString);
  return 0;
}

int DataBaseConnector::registerUser(std::string login, std::string password, int clientId)
{
  if(this->database.isUser(login)){
    return -3;
  }
  this->database.addUser(login, password);
  //zaloguj
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
  }
}
