#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include "CLI.hpp"
#include "Network.hpp"
#include "Output.hpp"

#include "../message.cpp"

using namespace std;

class Handling{

  Network &network;
  CLI &cli;
  Output &output;

  void setNetwork(Network &netw){
      network = netw;
  }

  void setCLI(CLI &cli1){
      cli = cli1;
  }

  void setOutput(Output &outp){
      output = outp;
  }

  void handleCommand(string command){
      if(command == "exit" || command == "stop"){
          //stopserver
      }
      else if(command == "close"){
          int socketNumber = cli.getSocketNumber();
          int error = network.disconnectClient(socketNumber);
          if(error == -2) output.cannotCloseServer();
          if(error == -1) output.socketDoesntExist();
          if(!error) output.sockedIsClosed();
      }
      else if(command == "help") output.help();
      else if(command == "list"){

      }
  }

}
