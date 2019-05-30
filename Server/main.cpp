#include <iostream>
#include <string>
#include <pthread.h>
#include <memory>
//FILE INCLUDES
#include "Controller/MainConstants.h"
#include "Controller/CLI.h"

int main(int argc, char* argv[])
{

  MainConstants constants(argc,argv);
  auto clients = make_shared<ClientSessionPipes>();
  CommandLineInterface CLI(constants.getMaxConnections() , constants.getServerPort() , constants.getServerIp() , clients);
  CLI.startCommandLine();

  /*
  Network siec(constants.getMaxConnections() , constants.getServerPort() , constants.getServerIp());
  if(siec.startServer() == -1){
    puts("Cannot run server!!!");
    return 1;
  }
  else{
    puts("Server running!!!");
    siec.waitForSignal();
  }*/

  return 0;
}
