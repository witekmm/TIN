#include <iostream>
#include <string>
#include <pthread.h>
//FILE INCLUDES
#include "Controller/MainInput.h"
int main(int argc, char* argv[])
{
  MainInput inputData(argc, argv);
  MainConstants constants(inputData.getConstants());

  return 0;
}
