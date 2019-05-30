#include "../ClientSession/ClientSessionPipes.h"

#ifndef CLI_H
#define CLI_H

#include "../Network/Network.h"
#include "../Logic/MessageHandler.h"
#include <pthread.h>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include <memory>
#include <functional>

class CommandLineInterface: public Network, public MessageHandler{
  bool working;
public:
  CommandLineInterface(int maxConnections, int port, std::string ip, std::shared_ptr<ClientSessionPipes> clients);
  void startCommandLine();

  bool handleCommand(std::vector<std::string> splitedCommand);

  bool checkIfStringIsNumber(std::string toCheck);

    void helpHandling();

    bool startHandling(std::vector<std::string> splitedCommand);
      void fullStartHandling();
      void startServerHandling();
      void startListeningHandling();
      void startWaitingHandling();

    bool stopHandling(std::vector<std::string> splitedCommand);
      void fullStopHandling();
      void stopWaitingHandling();

    bool setHandling(std::vector<std::string> splitedCommand);
      void setPortHandling(int port);
      void setMaxConnectionsHandling(int connections);

    bool addHandling(std::vector<std::string> splitedCommand);
      void addUserHandling(std::string login, std::string password);
      void addGroupHandling(std::string groupName, std::string adminLogin);

    bool deleteHandling(std::vector<std::string> splitedCommand);
      void deleteUserHandling(std::string login);
      void deleteGroupHandling(std::string groupName);

    bool closeHandling(std::vector<std::string> splitedCommand);

    bool closeByLoginHandling(std::vector<std::string> splitedCommand);


  static void * selectThreadWrapper(void * Object);
  static void * logicThreadWrapper(void * Object);
};

#endif
