#include <iostream>
#include <string>
#include <pthread.h>
//FILE INCLUDES
#include "Controller/MainConstants.h"

#include "Transport/Transport.h"
//#include "Network/Server.h"


int main(int argc, char* argv[])
{
  MainConstants constants(argc,argv);
  //stworzyc Transport
  //stworzyc handlemessage - dodac tam transport i
  //Stworzyc dla niego HandleDataBase - tam tworzy sie createReply
  //do createReply dodac transport
  //stworzy interface dodac tam handle message i na odwrot
  //stworzyc network dodac tam transport
  //network.startServer(constants.getMaxConnections() , constants.getServerPort() , constants.getServerIp());
  //1 watek to funkcja network.checkClientsMessagesLoop
  //2 watek to funkcja network.selectDescriptor
  //3 watek to funkcja interface.mainCommand



  return 0;
}
