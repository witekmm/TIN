#ifndef CLI_H
#define CLI_H

#include "../Network/Network.h"
#include <thread>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>

class CommandLineInterface: private Network{
  bool working;
public:
  CommandLineInterface(int maxConnections, int port, std::string ip);
  void getCommand();
  bool checkCommandsPropriety(std::vector<std::string> splitedCommand);
  bool handleCommand(std::vector<std::string> splitedCommand);
  bool commandExist(std::string command);
  void selectThreadWrapper();
};

#endif
