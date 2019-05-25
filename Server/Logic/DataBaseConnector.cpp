#include "DataBaseConnector.h"

DataBaseConnector::DataBaseConnector()
    : database(){}

void DataBaseConnector::sendGroupMessage(std::string content, std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    //wiadomosc
    return;
  }
  this->database.addMsgToGroup(groupName, login, 1, content);
  //wiadomosc
}

void DataBaseConnector::createGroup(std::string groupName, std::string login)
{
  if(this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  this->database.createGroup(groupName, login);
  //wiadomosc
}

void DataBaseConnector::deleteGroup(std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    //wiadomosc
    return;
  }
  database.deleteGroup(groupName);
  //wiadomosc
}

void DataBaseConnector::requestToGroup(std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  if(this->database.belongsToGroup(groupName , login)){
    //wiadomosc
    return;
  }

  //database.addMsgToUser(groupName, login);
}

void DataBaseConnector::acceptRequest(std::string groupName, std::string userName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    //wiadomosc
    return;
  }
  //sprawdz czy taki request istnieje i go usun z bazy danych
  this->database.addUserToGroup(groupName , userName);
}

void DataBaseConnector::declineRequest(std::string groupName, std::string userName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  int id = this->database.getUserId(login);
  if(!this->database.isAdministrator(groupName, id)){
    //wiadomosc
    return;
  }
  //sprawdz czy taki request istnieje
  this->database.addUserToGroup(groupName , userName);
}

void DataBaseConnector::leaveGroup(std::string groupName, std::string login)
{
  if(!this->database.isGroup(groupName)){
    //wiadomosc
    return;
  }
  if(!this->database.belongsToGroup(groupName , login)){
    //wiadomosc
    return;
  }
  int id = this->database.getUserId(login);
  if(this->database.isAdministrator(groupName, id)){
    this->database.removeAllUsersFromGroup(groupName);
    this->database.deleteGroup(groupName);
    return;
  }
  this->database.removeUserFromGroup(groupName, login);
}

int DataBaseConnector::logInUser(std::string login, std::string password)
{
  if(!this->database.isUser(login)){
    //wiadomosc
    return -1;
  }
  std::string temp = this->database.getUserPassword(login);
  if(password!=temp){
    //wiadomosc
    return -2;
  }
  //zaloguj
  //wyslij grupy
  return 0;
}

int DataBaseConnector::registerUser(std::string login, std::string password)
{
  if(this->database.isUser(login)){
    //wiadomosc
    return -3;
  }
  this->database.addUser(login, password);
  //zaloguj
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
