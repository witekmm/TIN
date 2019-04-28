using namespace std;
#include <string>
#include <iostream>
#include "Output.h"

void Output::serverIsClosed(){
    cout<<"Server is closed!"<<endl;
}
void Output::Output::cannotCloseServer(){
    cout<<"Cannot close server!"<<endl;
}
void Output::socketDoesntExist(int socketNumber){
    cout<<"Socket number "<<socketNumber<<" doesn't exist!"<<endl;
}
void Output::socketIsClosed(int socketNumber){
    cout<<"Socket number "<<socketNumber<< "is now closed"<<endl;
}
void Output::help(){
    cout<<"exit / stop - close server"<<endl;
    cout<<"close - disconnect choosen socket"<<endl;
    cout<<"list - show active sockets"<<endl;
    cout<<"server - show server's socket number"<<endl;
}
void Output::printNumber(int number){
    cout<<number<<endl;
}
void Output::cannotConnect(){
    cout<<"Cannot connect"<<endl;
}
void Output::connectionCreated(int socketNumber){
    cout<<"Connection created on socket number "<<socketNumber<<endl;
}
void Output::cannotReceive(int socketNumber){
    cout<<"Cannot receive data from socket number "<<socketNumber<<endl;
}
void Output::messageReceived(string message){
    cout<<"The message is:"<<endl<<message<<endl;
}
void Output::waitingForCommand(){
    cout<<"Input command:"<<endl;
}
