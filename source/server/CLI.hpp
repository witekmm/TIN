#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

#include "Handling.hpp"

class CLI{
  int working;
  Handling &handling;

public:

  CLI(){
      working=1;
  }

  void stopServer(){
      working = 0;
  }

  void setHandling(Handling &hand){
      handling = hand;
  }

  void commandLine(){
      string command;
      while( working ){
          getline(cin , cmd);
          handling.handleCommand();
      }
  }

}
