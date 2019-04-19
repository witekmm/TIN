#include <string>
#include "MainConstants.h"

std::string& MainConstants::getServerIp(){ return serverIp;}

int MainConstants::getServerPort(){ return serverPort;}

int MainConstants::getMaxConnections(){ return maxConnections;}

void MainConstants::setMaxConnections(int maxConnections){
  this->maxConnections=maxConnections;
}

void MainConstants::setServerPort(int serverPort){
  this->serverPort=serverPort;
}

void MainConstants::setServerIp(std::string serverIp){
  this->serverIp=serverIp;
}

MainConstants::MainConstants(std::string serverIp, int serverPort, int maxConnections){
  this->serverIp=serverIp;
  this->serverPort=serverPort;
  this->maxConnections=maxConnections;
}

MainConstants::MainConstants(MainConstants& toCopy){
  this->serverIp=toCopy.serverIp;
  this->serverPort=toCopy.serverPort;
  this->maxConnections=toCopy.maxConnections;
}
