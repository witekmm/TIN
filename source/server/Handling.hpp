#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include "CLI.hpp"
#include "Network.hpp"
#include "Output.hpp"
#include "Network.hpp"
#include "../message.cpp"
#include "Server.hpp"

using namespace std;

class Handling{

  Network &network;
  CLI &cli;
  Output &output;

public:

  Handling(CLI &cli1,Output& outp,Network &netw){
      output = outp;
      network = netw;
      cli = cli1;
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
          if(error == -1) output.socketDoesntExist(socketNumber);
          if(!error) output.socketIsClosed(socketNumber);
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

  //messageLen to ilość odebranych bajtów w recv()
  void handleMessage(char *message,int messageLen, int socketNumber){
      Message buffer(message , messageLen);
      int finalLength = messageLen;
      string finalMessage(buffer.getMessage());
      if(buffer.getSendLength() != messageLen){
          char* msg;
          while(msg = readNext(socketNumber) != NULL){
              Message temp(msg);
              string strTemp(temp.getMessage());
              finalMessage+=strTemp;
              finalLength+=strTemp.length();
          }
      }
      Message tmp(finalMessage);
      if(sendBack(tmp.getFullMessage(),tmp.getSendLength(),socketNumber)==-1){
          network.disconnectClient(socketNumber);
          output.socketIsClosed(socketNumber);
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
          if(!error) output.socketIsClosed(socketNumber);
      }
      else{
          output.messageReceived(command);
      }
  }
//PIPES
    void cannotCloseServer(){
        output.cannotCloseServer();
    }

    void incorrectSocket(int socketNumber){
        output.socketDoesntExist(socketNumber);
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

    void waitingForCommand(){
        output.waitingForCommand();// ma wypisać Input command: albo coś w tym stylu
    }

    void socketIsClosed(int socketNumber){
        output.socketIsClosed(socketNumber);
    }


}
