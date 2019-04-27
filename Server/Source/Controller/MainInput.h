#include <iostream>
using namespace std;

#ifndef MAIN_INPUT_H
#define MAIN_INPUT_H

#include "MainConstants.h"

#define DEFAULT_SERVER_PORT 50011
#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_MAX_CONNECTIONS 10

class MainInput{
  MainConstants constants;
  int argc;
  char* argv[];

public:
  MainInput(int argc, char* argv[]);

  void checkFlag();
  MainConstants getConstants();
  void setServerPort(int serverPort);
  void setMaxConnections(int maxConnections);
  void setServerIp(string serverIp);
};

#endif
