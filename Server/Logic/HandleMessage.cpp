#include "HandleMessage.h"
#include "../Transport/Transport.h"
#include "HandleDataBase.h"
#include "../Transport/Interface.h"

void HandleMessage::checkReceivedMessage(Message::ClientMessage message, string login,int socketNumber){
  if(!message.has_messagetype()){
    perror("Message is incorrect!");
    return;
  }

  if(message.messagetype() == Message::ClientMessage::GROUP){
    if(!this->transport.getNetwork().isClientLogged(socketNumber)){
      perror("Client is not logged in!");
      return;
    }
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
    this->transport.getNetwork().disconnectClient(login);
  }
  else if(message.commandtype() == Message::ClientMessage::LOG_OUT){
    this->transport.getNetwork().logOutClient(login);
  }
}

void HandleMessage::checkCommand(string command){
  if(command == "exit"){
    cout<<"Server will be closed!"<<endl;
    this->transport.getNetwork().closeServer();
  }
  else if(command == "disconnect"){
    cout<<"Please input user login:"<<endl;
    string login = this->interface.getString();
    if(this->transport.getNetwork().checkIfClient(login)){
      this->transport.getNetwork().disconnectClient(login);
      cout<<login<<" has been disconnected!"<<endl;
    }
    else{
      cout<<login<<" is not logged in!"<<endl;
    }
  }
  else if(command == "close"){
    cout<<"Please input user socket number:"<<endl;
    int socketNumber = this->interface.getNumber();
    if(this->transport.getNetwork().checkIfClient(socketNumber)){
      this->transport.getNetwork().disconnectClientBySN(socketNumber);
      cout<<socketNumber<<" has been closed!"<<endl;
    }
    else{
      cout<<socketNumber<<" is not connected!"<<endl;
    }
  }
  else if(command == "list"){
    vector<pair<string , int>> list = this->transport.getNetwork().getClientsList();
    for(int i = 0; i < list.size() ; i++){
      cout<<"SOCKET NUMBER = "<<list[i].second<<" LOGIN = "<<list[i].first<<endl;
    }
  }
  else if(command == "addgroup"){
    cout<<"Please input group name:"<<endl;
    string groupName = this->interface.getString();
    cout<<"Please input administrator name:"<<endl;
    string administrator = this->interface.getString();
    int result = this->database.rootAddGroup(groupName , administrator);
    if(result == -1){
      cout<<"Group with choosen name already exists!"<<endl;
    }
    if(result == -2){
      cout<<"User with choosen name doesn't exist!"<<endl;
    }
    if(result){
      cout<<"Group created!"<<endl;
    }
  }
  else if(command == "adduser"){
    cout<<"Please input login:"<<endl;
    string login = this->interface.getString();
    cout<<"Please input password:"<<endl;
    int password = this->interface.getStringAndEncode();
    if(this->database.rootAddUser(login, password)){
      cout<<"User created!"<<endl;
    }
    else{
      cout<<"User with choosen name already exists!"<<endl;
    }
  }
  else if(command == "deletegroup"){
    cout<<"Please input group name:"<<endl;
    string groupName = this->interface.getString();
    if(this->database.rootDeleteGroup(groupName)){
      cout<<"Group deleted!"<<endl;
    }
    else{
      cout<<"Group with choosen name doesn't exist!"<<endl;
    }
  }
  else if(command == "deleteuser"){
    cout<<"Please input user name:"<<endl;
    string login = this->interface.getString();
    if(this->database.rootDeleteUser(login)){
      cout<<"User deleted!"<<endl;
    }
    else{
      cout<<"User with choosen doesn't exist!"<<endl;
    }
  }
  return;
}

void HandleMessage::checkIfMessageExistAndSend(string login){
  this->database.checkIfMessageExistAndSend(login);
}
