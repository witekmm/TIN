#include <string>
#include <iostream>

#IFNDEF MAIN_CONSTANTS_H
#DEFINE MAIN_CONSTANTS_H

class MainConstants{
  const std::string serverIp;
  const int serverPort;
  const int maxConnections;

public:
  MainConstants(std::string serverIp, int serverPort, int maxConnections);
  MainConstants(const MainConstants& toCopy);

  std::string& getServerIp();
  int getServerPort();
  int getMaxConnections();

  void setServerIp(std::string serverIp);
  void setServerPort(int serverPort);
  void setMaxConnections(int maxConnections);

}

#ENDIF
