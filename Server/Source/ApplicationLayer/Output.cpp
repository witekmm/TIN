#include <string>
#include <iostream>
#include "Output.h"

void Output::serverIsClosed(){
    std::cout<<"Server is closed!"<<std::endl;
}
void Output::Output::cannotCloseServer(){
    std::cout<<"Cannot close server!"<<std::endl;
}
void Output::socketDoesntExist(int socketNumber){
    std::cout<<"Socket number "<<socketNumber<<" doesn't exist!"<<std::endl;
}
void Output::socketIsClosed(int socketNumber){
    std::cout<<"Socket number "<<socketNumber<< "is now closed"<<std::endl;
}
void Output::help(){
    std::cout<<"exit / stop - close server"<<std::endl;
    std::cout<<"close - disconnect choosen socket"<<std::endl;
    std::cout<<"list - show active sockets"<<std::endl;
    std::cout<<"server - show server's socket number"<<std::endl;
}
void Output::printNumber(int number){
    std::cout<<number<<std::endl;
}
void Output::cannotConnect(){
    std::cout<<"Cannot connect"<<std::endl;
}
void Output::connectionCreated(int socketNumber){
    std::cout<<"Connection created on socket number "<<socketNumber<<std::endl;
}
void Output::cannotReceive(int socketNumber){
    std::cout<<"Cannot receive data from socket number "<<socketNumber<<std::endl;
}
void Output::messageReceived(std::string message){
      std::cout<<"The message is:"<<std::endl<<message<<std::endl;
}
void Output::waitingForCommand(){
    std::cout<<"Input command:"<<std::endl;
}
