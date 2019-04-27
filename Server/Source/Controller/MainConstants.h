#include <string>
#include <iostream>

using namespace std;

#ifndef MAIN_CONSTANTS_H
#define MAIN_CONSTANTS_H

class MainConstants{
  const string serverIp;
  const int serverPort;
  const int maxConnections;

public:
  MainConstants(string serverIp, int serverPort, int maxConnections);
  MainConstants(const MainConstants& toCopy);

  string& getServerIp();
  int getServerPort();
  int getMaxConnections();

  void setServerIp(string serverIp);
  void setServerPort(int serverPort);
  void setMaxConnections(int maxConnections);

};

#endif
