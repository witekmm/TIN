using namespace std;
#include "Interface.h"
#include "../Logic/HandleMessage.h"

Interface::Interface()
{
  this->working=true;
}

Interface::~Interface()
{
  if(handleMessage!=nullptr)
    delete handleMessage;
}

void Interface::setHandleMessage(HandleMessage* hm)
{
  this->handleMessage = hm;
}

void Interface::mainCommand(){
  while(this->working){
    clearInput();
    string command;
    getline(cin , command);
    handleMessage->checkCommand(command);
  }
}

int Interface::getNumber(){
  clearInput();
  int number;
  cin>>number;
  return number;
}

string Interface::getString(){
  clearInput();
  string command;
  getline(cin , command);
  return command;
}

int Interface::getStringAndEncode(){
  clearInput();
  string command;
  getline(cin , command);
  hash<string> hashString;
  int hashed = hashString(command);
  return hashed;
}

void Interface::clearInput(){
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Interface::closeInterface(){
  this->working=false;
}
