#include "CLI.h"

CommandLineInterface::CommandLineInterface(int maxConnections, int port, std::string ip, std::shared_ptr<ClientSessionPipes> clients):
 Network(maxConnections,port,ip,clients), MessageHandler(clients) , working(true)
{}

void CommandLineInterface::getCommand(){

  //std::thread logicThread (&CommandLineInterface::logicThreadWrapper , this);
  //logicThread.detach();
  //pthread_t logicthread;
  //pthread_create(&logicthread, NULL, &CommandLineInterface::logicThreadWrapper, this);

//  std::thread dataBaseThread (&CommandLineInterface::dataBaseThreadWrapper , this);
//  dataBaseThread.detach();

  while(this->working){
    std::cin.clear();
    //clear buffer
    std::string command;
    puts("Command: ");
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
      if(!handleCommand(splitedCommand)) puts("Incorrect command!");
    }
    else{
      puts("Incorrect command!");
    }
  }
}
bool CommandLineInterface::checkCommandsPropriety(std::vector<std::string> splitedCommand){
  for(auto it = splitedCommand.begin() ; it!=splitedCommand.end() ; it++){
    if(it == splitedCommand.begin() && *it=="closebylogin") return true;
    if(it == splitedCommand.begin() && (*it=="add" || *it=="delete")) return true;
    if(!commandExist(*it)) return false;
  }
  return true;
}

bool CommandLineInterface::handleCommand(std::vector<std::string> splitedCommand){
  if(!splitedCommand.size()) return false;
  if(splitedCommand[0] == "help" || splitedCommand[0] == "-help"){
    puts("start server - obvious");
    puts("start listening - set server to passive mode");
    puts("start waiting  - start waiting on select");
    puts("stop server - obvious");
    puts("stop waiting - stop waiting on select");
    puts("set port NUMBER_OF_PORT - obvious");
    puts("set connections NUMBER_OF_CONNECTIONS - set max number of connections");
    puts("close NUMBER_OF_SOCKET - obvious");
    puts("add user user_name user_password");
    puts("add group group_name admin_name");
    puts("delete user user_name");
    puts("delete group group_name");
    puts("closebylogin CLIENT_LOGIN - obvious");
    return true;
  }
  //TU SIE ZACZYNA START
  else if(splitedCommand[0] == "start"){
    //tylko start
    if(splitedCommand.size() == 1) return false;
    //tworzymy socket i bindujemy do ip
    else if(splitedCommand[1] == "server"){
      //moze juz stworzony
      if(Network::ServerOperation::getIsSocketNumberSet()) {
        puts("Server already started!");
        return true;
      }
      //czy sie udalo stworzyc
      if(Network::startServer() == -1){
        puts("Cannot start server!");
      }
      return true;
    }
    //socket w tryb pasywny
    else if(splitedCommand[1] == "listening"){
      //czy stworzono socket
      if(!Network::ServerOperation::getIsSocketNumberSet()) {
        puts("Server not started!");
        return true;
      }
      //Czy juz jest pasywny
      if(Network::ServerOperation::getIsSocketListening()){
        puts("Socket already passive!");
        return true;
      }
      //czy udalo sie
      if(Network::ServerOperation::listenServerSocket() == -1){
        puts("Cannot set passive mode!");
      }
      return true;
    }
    //zaczynamy nasluchiwac
    else if(splitedCommand[1] == "waiting"){
      //czy stworzono socket
      //Czy jest pasywny
      if(!Network::ServerOperation::getIsSocketListening()){
        puts("Socket not passive!");
        return true;
      }
      //czy moze juz server nasluchuje

      if(Network::isServerWaiting()){
        puts("Socket already waiting!");
        return true;
      }
      //no to tworzymy watek
      puts("Server is waiting on socket!");
      pthread_t selectThread;
      pthread_create(&selectThread, NULL, &CommandLineInterface::selectThreadWrapper, this);
      return true;
    }
    else{
      return false;
    }
  }
  //TU SIE ZACZYNA STOP
  else if(splitedCommand[0] == "stop"){
    //czy jest cos po stop
    if(splitedCommand.size() == 1) return false;
    //czy stopujemy server
    else if(splitedCommand[1] == "server"){
      //czy stworzono socket
      if(!Network::ServerOperation::getIsSocketNumberSet()) {
        puts("Server not started!");
        return true;
      }
      //jak stworzono to go zamykamy i wszystkich klientow
      Network::closeServer();
      return true;
    }
    else if(splitedCommand[1] == "waiting"){
      //czy server nasluchuje
      if(!Network::isServerWaiting()){
        puts("Server not started!");
      }
      //jesli tak to wstrzymujemy nasluchiwanie ale klientow zatrzymujemy
      Network::stopWaiting();
      return true;
    }
    else{
      return false;
    }
  }
  //TU ZACZYNA SIE SET
  else if(splitedCommand[0] == "set"){
    //czy jest cos po set
    if(splitedCommand.size() < 3) return false;
    //ustawiamy port
    else if(splitedCommand[1] == "port"){
      if(Network::ServerOperation::getIsSocketNumberSet()) {
        puts("Cannot set port while server working!");
        return true;
      }
      //sprawdzamy czy to wgl liczba
      for(auto it = splitedCommand[2].begin() ; it!=splitedCommand[2].end() ; it++){
        if(!std::isdigit(*it)) return false;
      }
      //sprawdzamy jaka to liczba
      int number = std::stoi(splitedCommand[2]);
      if(number > 65535 || number < 49152 ){
        puts("Incorrect port number!");
        return true;
      }
      std::cout<<"New port number is:"<<number<<std::endl;
      Network::ServerOperation::setPort(number);
      return true;
    }
    else if(splitedCommand[1] == "connections"){
      if(Network::ServerOperation::getIsSocketNumberSet()) {
        puts("Cannot set maxconnections while server working!");
        return true;
      }
      //sprawdzamy czy to wgl liczba
      for(auto it = splitedCommand[2].begin() ; it!=splitedCommand[2].end() ; it++){
        if(!std::isdigit(*it)) return false;
      }
      //sprawdzamy jaka to liczba
      int number = std::stoi(splitedCommand[2]);
      if(number < 0  || number > 1000 ){
        puts("Incorrect connections number");
        return true;
      }
      std::cout<<"New connections number is:"<<number<<std::endl;
      Network::ServerOperation::setConnections(number);
      return true;
    }
    else{
      return false;
    }

  }
  else if(splitedCommand[0] == "close"){
    if(splitedCommand.size() == 1) return false;
    //sprawdzamy czy to wgl liczba
    for(auto it = splitedCommand[1].begin() ; it!=splitedCommand[1].end() ; it++){
      if(!std::isdigit(*it)) return false;
    }
    int number = std::stoi(splitedCommand[1]);
    int result = Network::closeSocketWithBlocking(number);
    //zamykanie serwera
    if(result == 1){
      puts("Cannot close server socket");
      return true;
    }
    //zamykanie nieistniejacego socketa
    else if(result == 2){
      puts("Socket doesnt exist");
      return true;
    }
    else{
      puts("Socket closed");
      return true;
    }
  }
  else if(splitedCommand[0] == "closebylogin"){
    return false;
  }
  else if(splitedCommand[0] == "add"){
    if(splitedCommand.size() != 4) return false;
    if(splitedCommand[1] == "user"){
      std::hash<std::string> hasher;
      std::string password = std::to_string(hasher(splitedCommand[3]));
      int result = MessageHandler::DataBaseConnector::rootAddUser(splitedCommand[2], password);
      if(result == -1){
        puts("Login already in use!");
        return true;
      }
      puts("User created");
      return true;
    }
    else if(splitedCommand[1] == "group"){
      int result = MessageHandler::DataBaseConnector::rootAddGroup(splitedCommand[2], splitedCommand[3]);
      if(result == -1){
        puts("User passed as admin doesn't exist!");
        return true;
      }
      else if(result == -2){
        puts("Group already exist!");
        return true;
      }
      puts("Group created");
      return true;
    }
    else return false;
  }
  else if(splitedCommand[0] == "delete"){
    if(splitedCommand.size() != 3) return false;
    if(splitedCommand[1] == "user"){
      if(MessageHandler::DataBaseConnector::rootDeleteUser(splitedCommand[2]) == -1){
        puts("User doesn't exist!");
        return true;
      }
      puts("User deleted!");
      return true;
    }
    else if(splitedCommand[1] == "group"){
      if(MessageHandler::DataBaseConnector::rootDeleteGroup(splitedCommand[2]) == -1){
        puts("Group doesn't exist!");
        return true;
      }
      puts("Group deleted!");
      return true;
    }
    else return false;
  }
  else return false;
}

bool CommandLineInterface::commandExist(std::string command){
  if(command == "start"){
    return true;
  }
  else if(command == "server"){
    return true;
  }
  else if(command == "help"){
    return true;
  }
  else if(command == "-help"){
    return true;
  }
  else if(command == "listening"){
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
  else if(command == "connections"){
    return true;
  }
  else if(command == "add"){
    return true;
  }
  else if(command == "delete"){
    return true;
  }
  else if(command == "user"){
    return true;
  }
  else if(command == "group"){
    return true;
  }
  else{
    for(auto it = command.begin() ; it!=command.end() ; it++){
      if(!std::isdigit(*it)) return false;
    }
    return true;
  }
}

void * CommandLineInterface::selectThreadWrapper(void * Object){
  ((CommandLineInterface *)Object)->Network::waitForSignal();
}

void CommandLineInterface::dataBaseThreadWrapper(){
  MessageHandler::LogicThreadLoop();
}

void * CommandLineInterface::logicThreadWrapper(void * Object){
  ((CommandLineInterface *)Object)->MessageHandler::DataBaseMessageCheckLoop();
}
