#include <iostream>
#include <string>
#include <pthread.h>
#include <thread>
//FILE INCLUDES
#include "Controller/MainConstants.h"

#include "Transport/Transport.h"
//#include "Network/Server.h"
#include "Logic/HandleDataBase.h"

int main(int argc, char* argv[])
{
  MainConstants constants(argc,argv);
  //stworzyc Transport
  Transport transport;
  //stworzyc handlemessage - dodac tam transport i
  CreateReply reply(transport);
  HandleDataBase dataBase(reply);

  Interface interface;
  HandleMessage handleMessage(transport, dataBase, interface);
  interface.setHandleMessage(&handleMessage);
  //Stworzyc dla niego HandleDataBase - tam tworzy sie createReply
  //do createReply dodac transport
  //stworzy interface dodac tam handle message i na odwrot
  //stworzyc network dodac tam transport
  Network network(transport);

  network.startServer(constants.getMaxConnections() , constants.getServerPort() , constants.getServerIp());
  //1 watek to funkcja network.checkClientsMessagesLoop
  //2 watek to funkcja network.selectDescriptor
  //3 watek to funkcja interface.mainCommand
  std::thread t1(&Network::checkClientsMessagesLoop, network);
  std::thread t2(&Network::selectDescriptor, network);
  std::thread t3(&Interface::mainCommand, handleMessage.getInterface());

  return 0;
}
