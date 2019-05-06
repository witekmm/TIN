using namespace std;
#include "Interface.h"
#include "../Logic/HandleMessage.h"

Interface::Interface(){
  this->working=true;
}

void Interface::mainCommand(){
  while(this->working){
    clearInput();
    string command;
    getline(cin , command);
    this->handleMessage.checkCommand(command);
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
