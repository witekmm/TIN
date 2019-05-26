#include "../ClientSession/ClientSessionPipes.h"

#ifndef CLI_H
#define CLI_H

#include "../Network/Network.h"
#include "../Logic/MessageHandler.h"
#include <thread>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include <memory>
#include <functional>

class CommandLineInterface: private Network, private MessageHandler{
  bool working;
public:
  CommandLineInterface(int maxConnections, int port, std::string ip, std::shared_ptr<ClientSessionPipes> clients);
  void getCommand();
  bool checkCommandsPropriety(std::vector<std::string> splitedCommand);
  bool handleCommand(std::vector<std::string> splitedCommand);
  bool commandExist(std::string command);
  void selectThreadWrapper();
};

#endif
