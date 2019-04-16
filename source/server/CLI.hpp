#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include "Handling.hpp"

using namespace std;

class CLI{
  Handling &handling;

public:

  void setHandling(Handling &hand){
      handling = hand;
  }

  void commandLine(){
      string command;
      getline(cin , command);
      handling.handleCommand(command);
  }

  int getSocketNumber(){
      int socketNumber;
      cin>>socketNumber;
      return socketNumber;
  }

}
