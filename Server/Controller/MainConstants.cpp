#include <string>
#include <iostream>
#include "MainConstants.h"

using namespace std;

string& MainConstants::getServerIp(){ return this->serverIp;}

int MainConstants::getServerPort(){ return this->serverPort;}

int MainConstants::getMaxConnections(){ return this->maxConnections;}

MainConstants::MainConstants(int argc , char* argv[])
{
  string tmp(DEFAULT_SERVER_IP);
  this->serverIp = tmp;
  this->serverPort = DEFAULT_SERVER_PORT;
  this->maxConnections = DEFAULT_MAX_CONNECTIONS;
  checkFlag(argc, argv);
}

void MainConstants::checkFlag(int arg, char* argv[])
{
  int argc = arg;
  while(!argc)
  {
    string value(argv[argc-1]);
    if(value == "-p")
    {
      this->serverPort = atoi(argv[argc]);
    }
    else if(value == "-c")
    {
      this->maxConnections = atoi(argv[argc]);
    }
    else if(value == "-i")
    {
      string ip(argv[argc]);
      this->serverIp = ip;
    }
    argc -= 2;
  }
}
