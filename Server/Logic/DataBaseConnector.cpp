#include "DataBaseConnector.h"

DataBaseConnector::DataBaseConnector()
    : database(){}

void DataBaseConnector::sendGroupMessage(std::string content, std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group doesn't exist");
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    Reply::incorrectGroupTypeMessage(login, "You can't send message to group you do not belong");
    return;
  }
  this->database.addMsgToGroup(groupName, login, 1, content);
  Reply::correctMessage(login);
}

void DataBaseConnector::createGroup(std::string groupName, std::string login)
{
  if(this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group name already in use");
    return;
  }
  this->database.createGroup(groupName, login);
  Reply::correctMessage(login);
}

void DataBaseConnector::deleteGroup(std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectGroupTypeMessage(login, "You can't delete group you are not a administrator");
    return;
  }
  this->database.deleteGroup(groupName);
  Reply::correctMessage(login);
}

void DataBaseConnector::requestToGroup(std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group doesn't exist");
    return;
  }
  if(this->database.belongsToGroup(groupName , login)){
    Reply::incorrectGroupTypeMessage(login, "You already belong to choosen group");
    return;
  }
  //tu jeszcze dodania zapytania do bazy
  Reply::correctMessage(login);
}

void DataBaseConnector::acceptRequest(std::string groupName, std::string userName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectGroupTypeMessage(login, "You have no right to reply for request");
    return;
  }
  //sprawdz czy taki request istnieje i go usun z bazy danych
  this->database.addUserToGroup(groupName , userName);
  Reply::correctMessage(login);
}

void DataBaseConnector::declineRequest(std::string groupName, std::string userName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group doesn't exist");
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    Reply::incorrectGroupTypeMessage(login, "You have no right to reply for request");
    return;
  }
  //sprawdz czy taki request istnieje
  Reply::correctMessage(login);
}

void DataBaseConnector::leaveGroup(std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    Reply::incorrectGroupTypeMessage(login, "Group doesn't exist");
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    Reply::incorrectGroupTypeMessage(login, "You can't leave group you don't belong");
    return;
  }
  int id = this->database.getUserId(login);
  if(this->database.isAdministrator(groupName, id)){
    this->database.removeAllUsersFromGroup(groupName);
    this->database.deleteGroup(groupName);
    return;
  }
  this->database.removeUserFromGroup(groupName, login);
  Reply::correctMessage(login);
}

int DataBaseConnector::logInUser(std::string login, std::string password)
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
  Reply::correctLoginMessage(login, groupsByString);
  return 0;
}

int DataBaseConnector::registerUser(std::string login, std::string password)
{
  if(this->database.isUser(login)){
    return -3;
  }
  this->database.addUser(login, password);
  //zaloguj
  Reply::correctMessage(login);
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
