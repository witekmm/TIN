#include <iostream>
#include <string>
#include <pthread.h>
//FILE INCLUDES
#include "Controller/MainConstants.h"

//#include "Transport/Transport.h"
#include "Network/Server.h"


int main(int argc, char* argv[])
{
  MainConstants constants(argc,argv);

  Server server;
  server.createServerSocket();
  server.bindServerSocket();
  server.listenServerSocket();


  return 0;
}
