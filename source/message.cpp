#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstdlib>
#include <cstring> // strlen()
#include <stdbool.h>
#include <string.h>
#include <string> // string

using namespace std;

class Message{

  char header[10];
  char message[256];

public:
  //konstruktor tworzący MESSAGE z czystej wiadomości
  //w header zostawia liczbę
  Message(string mess){
    int length = strlen(mess);
    sprintf(header, "%10d", length);
    for(int x=0; x<10; x++){
        if(header[x] == ' ') header[x] = 'A';
        message[x] = header[x];
    }

    for(int x=10; x<255; x++){
      if(mess[x-10]=='\0') break;
      message[x]=mess[x-10];
    }
    int s = mess.length();
    message[s+10] = '\0';
    sprintf(header, "%10d", length);
  }
  //konstruktor tworzący MESSAGE z wiadomości składającej
  //się z danych i nagłówka
  Message(char* mess,int length){
      for(int i = 0;i < length;i++){
          message[i] = mess[i];
      }
      for(int i = 0;i<10;i++){
          if(mess[i] == 'A') header[i] = ' ';
          else header[i] = mess[i];
      }
  }

  Message(char* mess){
      for(int i = 0 ; i < strlen(mess) ;i++){
          message[i] = mess[i];
      }
      for(int i = 0;i<10;i++){
          if(mess[i] == 'A') header[i] = ' ';
          else header[i] = mess[i];
      }
  }
  //pobiera długość całego pliku razem z nagłówkiem
  //zwraca w int
  int getHeaderInInteger(){
      return atoi(header);

  }

  char* getMessage(){
      char temp[256];
      for(int i = 0 ; i < (getHeaderInInteger()-10) ; i++){
          temp[i] = message[i+10];
      }
      temp[getHeaderInInteger()-10] = '\0';
      return temp;
  }

  char* getFullMessage()
  {
    return this->message;
  }

  int getSendLength(){
      return strlen(message) + 1;
  }

};
