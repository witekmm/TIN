#include <string>
#include <iostream>
#include "MainConstants.h"

using namespace std;

string MainConstants::getServerIp(){ return this->serverIp;}

int MainConstants::getServerPort(){ return this->serverPort;}

int MainConstants::getMaxConnections(){ return this->maxConnections;}

MainConstants::MainConstants(int argc, char* argv[])
  : serverIp(DEFAULT_SERVER_IP), serverPort(DEFAULT_SERVER_PORT), maxConnections(DEFAULT_MAX_CONNECTIONS)
{
  checkFlag(argc, argv);
}

void MainConstants::checkFlag(int arg, char* argv[])
{
  int argc = arg;
  while(argc != 1)
  {
    string value(argv[argc-2]);
    if(value == "-p")
    {
      string temp(argv[argc-1]);
      if(!checkIfNumber(temp)){
        puts("Incorrect port number!\nDefault port number will be set!");
        break;
      }
      int number = stoi(temp);
      if(number > 65535 || number < 49152 ){
        puts("Incorrect port number!\nDefault port number will be set!");
        break;
      }
      this->serverPort = number;
    }
    else if(value == "-c")
    {
      string temp(argv[argc-1]);
      if(!checkIfNumber(temp)){
        puts("Incorrect connections number!\nDefault max connections number will be set!");
        break;
      }
      int number = stoi(temp);
      if(number > 1000 || number < 1 ){
        puts("Incorrect connections number!\nDefault max connections number will be set!");
        break;
      }
      this->maxConnections = number;
    }
    else if(value == "-i")
    {
      string temp(argv[argc-1]);
      std::istringstream split(temp);
      vector<string> splitedIP;
      string each;
      while(getline(split, each, '.')){
        splitedIP.push_back(each);
      }
      if(splitedIP.size() != 4){
        puts("Incorrect IP number!\nDefault IP will be set!");
        break;
      }
      bool flag = false;
      for(auto it = splitedIP.begin() ; it != splitedIP.end() ; it++){
        if(!checkIfNumber(*it)){
          puts("Incorrect IP number!\nDefault IP will be set!");
          flag = true;
          break;
        }
        if( 0 > stoi(*it) > 255){
          puts("Incorrect IP number!\nDefault IP will be set!");
          flag = true;
          break;
        }
      }
      if(flag==true) break;
      this->serverIp = string(argv[argc-1]);
    }
    argc -= 2;
  }
}

bool MainConstants::checkIfNumber(string toCheck){
  for(auto it = toCheck.begin() ; it!=toCheck.end() ; it++){
    if(!isdigit(*it)){
      return false;
    }
  }
  return true;
}
