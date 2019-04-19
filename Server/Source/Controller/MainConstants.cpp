#include <string>
#include "MainConstants.h"

std::string& MainConstants::getServerIp(){ return serverIp;}

int MainConstants::getServerPort(){ return serverPort;}

int getMaxConnections::getMaxConnections(){ return maxConnections;}

MainConstants(std::string serverIp, int serverPort, int maxConnections){
  this->serverIp=serverIp;
  this->serverPort=serverPort;
  this->maxConnections=maxConnections;
}

MainConstants(MainConstants& toCopy){
  this->serverIp=toCopy.serverIp;
  this->serverPort=toCopy.serverPort;
  this->maxConnections=toCopy.maxConnections;
}
