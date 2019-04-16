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

  void commandLine(int *flag, int *fd_val, int *flag_error){
       string cmd;
       while(flag){
          printf("Input command: ");
          getline(cin, cmd);
          if(cmd == "exit"){
              *flag = 0;
          }
          else if(cmd == "help"){
              puts("exit - close server and CLI.");
              puts("list - show active sockets.");
              puts("server - show server socket number.");
              puts("close - disconnect socket.");
          }
          else if(cmd == "close"){
              int fdval = 0;
              puts("Which socket:");
              scanf("%d", &fdval);
              while ((getchar()) != '\n');
              *fd_val = fdval;
              *flag = 2;
              while(*flag == 2); //czekamy az drugi wątek zamknie
              //Taki socket nie istnieje
              if(*flag_error == 1) puts("Cant find this socket!\n");
              //Probujemy zamknac np. serwer
              else if(*flag_error == 2) puts("You can't close this socket!\n");
              else puts("Socket closed :)\n");
          }
          else if(cmd == "list"){
              *flag = 3;
              int lastfd = 0;
              while(*flag == 3){
                  if((*fd_val != 0) && (*fd_val != lastfd)){ //sprawdz czy juz zapisal i czy my go zapisalismy
                      printf("%d\t", *fd_val); //wypisz fd
                      lastfd = *fd_val; // zapisz ostatni fd
                      *fd_val=0; //wyczyszczenie fd_val dla kolejnego numeru fd
                  }
              }
              puts("");
          }
          else if(cmd == "server"){
              *flag = 4;
              while(*flag == 4);
              printf("Server socket number is %d\n", *fd_val);
              *fd_val = 0;
          }
          else{
              printf("Cannot recognize this command!\n");
          }
       }
  }


}
