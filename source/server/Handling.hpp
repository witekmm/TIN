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

public:

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
          closeAllSockets();
          network.closeServerSocket();
          output.serverIsClosed();
          return;
      }
      else if(command == "close"){
          int socketNumber = cli.getSocketNumber();
          int error = network.disconnectClient(socketNumber);
          if(error == -2) output.cannotCloseServer();
          if(error == -1) output.socketDoesntExist();
          if(!error) output.sockedIsClosed(socketNumber);
      }
      else if(command == "help") output.help();
      else if(command == "server") output.printNumber(network.getServerSocket());
      else if(command == "list") getSocketList();
      cli.commandLine();
  }


  void getSocketList(){
      for(int i = network.getFdMax() ; i>0 ; i--){
          if(network.checkIfSocket(i) == -1) continue;
          else output.printNumber(i);
      }
  }

  void closeAllSockets(){
      for(int i = network.getFdMax() ; i>0 ; i--){
          if(network.checkIfSocket(i) == -1) continue;
          else network.disconnectClient(i);
      }
  }

  void cannotConnect(){
      output.cannotConnect();
  }

  void connectionCreated(int socketNumber){
      output.connectionCreated(socketNumber);
  }

  void cannotReceive(int socketNumber){
      output.cannotReceive(socketNumber);
  }
  //messageLen to ilość odebranych bajtów w recv()
  void handleMessage(char *message,int messageLen, int socketNumber){
      Message buffer(message , messageLen);
      string finalMessage(buffer.getMessage());
      if((buffer.getHeaderInInteger+10) != messageLen){
          char* msg;
          while(msg = readNext(socketNumber) != NULL){
              Message temp(msg);
              string strTemp(temp.getMessage());
              finalMessage+=strTemp;
          }
      }
      if(sendBack(buffer.getFullMessage(),buffer.getHeaderInInteger()+10,socketNumber)==-1){
          network.disconnectClient(socketNumber);
          output.sockedIsClosed(socketNumber);
      }
      handleClientCommand(finalMessage,socketNumber);
  }

  void handleClientCommand(string command, int socketNumber){
      if(command == "exit" || command == "stop"){
          closeAllSockets();
          network.closeServerSocket();
          output.serverIsClosed();
          return;
      }
      else if(command == "close"){
          int error = network.disconnectClient(socketNumber);
          if(!error) output.sockedIsClosed(socketNumber);
      }
      else{
          output.messageReceived(command);
      }
  }

  void handling.waitingForCommand(){
      output.waitingForCommand();// ma wypisać Input command: albo coś w tym stylu
  }



}
