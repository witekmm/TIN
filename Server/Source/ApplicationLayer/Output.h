#include <string>
#include <iostream>

#IFNDEF OUTPUT_H
#DEFINE OUTPUT_H

class Output{
public:
  //Server outputs
  void serverIsClosed();
  void cannotCloseServer();
  //Connecting outputs
  void connectionCreated(int socketNumber);
  void socketIsClosed(int socketNumber);
  void cannotConnect();
  void socketDoesntExist(int socketNumber);
  //Transport outputs
  void messageReceived(std::string message);
  void cannotReceive(int socketNumber);
  //Other outputs
  void help();
  void printNumber(int number);
  void waitingForCommand();

}

#ENDIF
