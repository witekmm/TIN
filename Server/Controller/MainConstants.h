#ifndef MAIN_CONSTANTS_H
#define MAIN_CONSTANTS_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#define DEFAULT_SERVER_PORT 50011
#define DEFAULT_SERVER_IP "127.0.0.12"
#define DEFAULT_MAX_CONNECTIONS 10

class MainConstants{
  string serverIp;
  int serverPort;
  int maxConnections;

public:
  MainConstants(int argc, char* argv[]);

  string getServerIp();
  int getServerPort();
  int getMaxConnections();
  void checkFlag(int argc, char* argv[]);

  bool checkIfNumber(string toCheck);
};

#endif
