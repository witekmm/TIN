#include "CLI.h"

CommandLineInterface::CommandLineInterface(int maxConnections, int port, std::string ip): Network(maxConnections,port,ip) , working(true)
{}

void CommandLineInterface::getCommand(){
  while(this->working){
    std::cin.clear();
    //clear buffer
    std::string command;
    std::getline(std::cin , command);
    //get command
    std::istringstream split(command);
    std::vector<std::string> splitedCommand;
    std::string each;
    while(std::getline(split, each, ' ')){
      splitedCommand.push_back(each);
    }
    //split command into words
    if(checkCommandsPropriety(splitedCommand)){
      if(handleCommand(splitedCommand) puts("Correct command!");
      else puts("Incorrect command!");
    }
    else{
      puts("Incorrect command!");
    }
  }
}
bool CommandLineInterface::checkCommandsPropriety(std::vector<std::string> splitedCommand){
  for(auto it = splitedCommand.begin() ; it!=splitedCommand.end() ; it++){
    if(!commandExist(*it)) return false;
  }
  return true;
}

bool CommandLineInterface::handleCommand(std::vector<std::string> splitedCommand){
  if(splitedCommand[0] == "help" || splitedCommand[0] == "-help"){
    puts("start server - obvious");
    puts("start listening - set server to passive mode");
    puts("stop listening - set server to passive mode");
  }
}

bool CommandLineInterface::commandExist(std::string command){
  if(command == "start"){
    return true;
  }
  else if(command == "server"){
    return true;
  }
  else if(command == "listening"){
    return true;
  }
  else if(command == "watching"){
    return true;
  }
  else if(command == "waiting"){
    return true;
  }
  else if(command == "set"){
    return true;
  }
  else if(command == "port"){
    return true;
  }
  else if(command == "stop"){
    return true;
  }
  else if(command == "close"){
    return true;
  }
  else{
    for(auto it = command.begin() ; it!=command.end() ; it++){
      if(!std::isdigit(*it)) return false;
    }
    return true;
  }

}
