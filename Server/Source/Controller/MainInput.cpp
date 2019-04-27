#include <string>
#include <stdlib.h>
using namespace std;

#include "MainInput.h"

MainInput::MainInput(int argc, char* argv[]){
  this->constants(string(DEFAULT_SERVER_IP) , DEFAULT_SERVER_PORT , DEFAULT_MAX_CONNECTIONS);
  this->argc=argc-1;
  this->argv=argv;
}

void MainInput::checkFlag(){
  while(!argc){
    string value(this->argv[this->argc-1]);
    if(value == "-p"){
      int port=atoi(this->argv[argc]);
      setServerPort(port);
    }
    if(value == "-c"){
      int connections=atoi(this->argv[argc]);
      setMaxConnections(connections);
    }
    if(value == "-i"){
      string ip(this->argv[argc]);
      setServerIp(ip);
    }
    this->argc-=2;
  }
}

MainConstants MainInput::getConstants(){
  return this->constants;
}

void MainInput::setServerPort(int serverPort){
  this->constants.setServerPort(serverPort);
}

void MainInput::setMaxConnections(int maxConnections){
  this->constants.setMaxConnections(maxConnections);
}

void MainInput::setServerIp(string serverIp){
  this->constants.setServerIp(serverIp);
}
