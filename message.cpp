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

  Message(string mess){

    int length = strlen(mess);
    sprintf(header, "%10d", length);

    for(int x=0; x<10; x++)
    {
      if(header[x] == NULL) //continue;
        header[x] = '0';
    }

    for(int x=0; x<10; x++){
      message[x] = header[x];
    }

    for(int x=10; x<255; x++){
      if(mess[x-10]=='\0') break;
      message[x]=mess[x-10];
    }
    message[strlen(message)] = '\0';
  }

  char* getMessage()
  {
    return this->message;
  }


};

int main()
{
  string str = "Przykladowy ciag znakow";
  Message mess(str);
  cout<<(string)mess.wiadomosc<<endl;

}
