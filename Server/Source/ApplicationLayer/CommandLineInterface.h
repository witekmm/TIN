#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#IFNDEF COMMAND_LINE_INTERFACE_H
#DEFINE COMMAND_LINE_INTERFACE_H

class CLI{

public:

  void setHandling(Handling &hand){
      handling = hand;
  }

  void commandLine(){
      string command;
      handling.waitingForCommand();
      getline(cin , command);
      handling.handleCommand(command);
  }

  int getSocketNumber(){
      int socketNumber;
      cin>>socketNumber;
      return socketNumber;
  }

}

#ENDIF
