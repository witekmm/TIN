#include <string>
using namespace std;
#include "MainConstants.h"

string& MainConstants::getServerIp(){ return serverIp;}

int MainConstants::getServerPort(){ return serverPort;}

int MainConstants::getMaxConnections(){ return maxConnections;}

void MainConstants::setMaxConnections(int maxConnections){
  this->maxConnections=maxConnections;
}

void MainConstants::setServerPort(int serverPort){
  this->serverPort=serverPort;
}

void MainConstants::setServerIp(string serverIp){
  this->serverIp=serverIp;
}

MainConstants::MainConstants(string serverIp, int serverPort, int maxConnections){
  this->serverIp=serverIp;
  this->serverPort=serverPort;
  this->maxConnections=maxConnections;
}

MainConstants::MainConstants(MainConstants& toCopy){
  this->serverIp=toCopy.serverIp;
  this->serverPort=toCopy.serverPort;
  this->maxConnections=toCopy.maxConnections;
}
