#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <cstring> // strlen()
#include <stdbool.h>
#include <string> // string

using namespace std;

Class Output{

public:

  void serverIsClosed(){
      cout<<"Server is closed!"<<endl;
  }
  void cannotCloseServer(){
      cout<<"You can't close server!"<<endl;
  }
  void socketDoesntExist(int socketNumber){
      cout<<"Socket number "<<socketNumber<<" doesn't exist!"<<endl;
  }
  void sockedIsClosed(int socketNumber){
      cout<<"Socket number "<<socketNumber<< "is now closed"<<endl;
  }
  void help(){
      cout<<"exit / stop - close server"<<endl;
      cout<<"close - disconnect choosen socket"<<endl;
      cout<<"list - show active sockets"<<endl;
      cout<<"server - show server's socket number"<<endl;
  }
  void printNumber(int number){
      cout<<number<<endl;
  }
  void cannotConnect(){
      cout<<"Cannot connect"<<endl;
  }
  void connectionCreated(int socketNumber){
      cout<<"Connection created on socket number "<<socketNumber<<endl;
  }
  void cannotReceive(int socketNumber){
      cout<<"Cannot receive data from socket number "<<socketNumber<<endl;
  }
  void messageReceived(string message){
      cout<<"The message is:"<<endl<<message<<endl;
  }
  void waitingForCommand(){
      cout<<"Input command:"<<endl;
  }


}
