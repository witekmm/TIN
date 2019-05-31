#include <iostream>
#include <string>
#include <pthread.h>
#include <memory>
//FILE INCLUDES
#include "Controller/MainConstants.h"
#include "Controller/CLI.h"

int main(int argc, char* argv[])
{

  MainConstants constants(argc, argv);
  auto clients = make_shared<ClientSessionPipes>();
  CommandLineInterface CLI(constants.getMaxConnections() , constants.getServerPort() , constants.getServerIp() , clients);
  CLI.startCommandLine();
  return 0;
}
