#include <iostream>
#include <pthread.h>
//FILE INCLUDES
#include "Controller/MainInput.h"
int main(int argc, char*argv[])
{
  MainInput inputData(argc, argv);
  MainConstants constants(MainInput.constants);

  return 0;
}
