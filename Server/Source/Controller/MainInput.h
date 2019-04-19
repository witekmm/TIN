#include <iostream>

#IFNDEF MAIN_INPUT_H
#DEFINE MAIN_INPUT_H

#include "MainConstants.h"

#DEFINE DEFAULT_SERVER_PORT 50011
#DEFINE DEFAULT_SERVER_IP "127.0.0.1"
#DEFINE DEFAULT_MAX_CONNECTIONS 10

class MainInput{
  MainConstants constants;
  int elements;

public:
  MainInput(int argc, char* argv[]);

}

#ENDIF
