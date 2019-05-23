#include <iostream>
#include <string>
#include <pthread.h>
//FILE INCLUDES
#include "Controller/MainConstants.h"
#include "Network/Network.h"

int main(int argc, char* argv[])
{

  MainConstants constants(argc,argv);
  Network siec(constants.getMaxConnections() , constants.getServerPort() , constants.getServerIp());
  if(siec.startServer() == -1){
    puts("Cannot run server!!!");
    return 1;
  }
  else{
    puts("Server running!!!");
    siec.waitForSignal();
  }
  return 0;
}
