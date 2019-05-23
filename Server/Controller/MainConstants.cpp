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
      this->serverPort = atoi(argv[argc-1]);
    }
    else if(value == "-c")
    {
      this->maxConnections = atoi(argv[argc-1]);
    }
    else if(value == "-i")
    {
      this->serverIp = string(argv[argc-1]);
    }
    argc -= 2;
  }
}
