#include "CLI.h"

CommandLineInterface::CommandLineInterface(int maxConnections, int port, std::string ip, std::shared_ptr<ClientSessionPipes> clients):
 Network(maxConnections,port,ip,clients), MessageHandler(clients) , working(true)
{}

void CommandLineInterface::startCommandLine(){

  pthread_t logicthread;
  pthread_create(&logicthread, NULL, &CommandLineInterface::logicThreadWrapper, this);

  while(this->working){
    std::cin.clear();
    //clear buffer
    std::string command;
    puts("COMMAND: ");
    std::getline(std::cin , command);
    //get command
    std::istringstream split(command);
    std::vector<std::string> splitedCommand;
    std::string each;
    while(std::getline(split, each, ' ')){
      splitedCommand.push_back(each);
    }
    //split command into words
    if(!handleCommand(splitedCommand)) puts("Incorrect command!");
  }

  pthread_cancel(logicthread);
}

bool CommandLineInterface::handleCommand(std::vector<std::string> splitedCommand){
  //sprawdzam czy komenda nie jest pusta
  if(!splitedCommand.size()) return false;
  //usuwam z vectora pierwszy element bo og odczytalem i zapisalem do tymczasowej zmiennej
  auto it = splitedCommand.begin();
  std::string command = *it;
  splitedCommand.erase(it);
  //obsluga
  if(command == "help" || command == "-help"){
    helpHandling();
    return true;
  }
  else if(command == "start"){
    return startHandling(splitedCommand);
  }
  else if(command == "stop"){
    return stopHandling(splitedCommand);
  }
  else if(command == "set"){
    return setHandling(splitedCommand);
  }
  else if(command == "close"){
    return closeHandling(splitedCommand);
  }
  else if(command == "add"){
    return addHandling(splitedCommand);
  }
  else if(command == "delete"){
    return deleteHandling(splitedCommand);
  }
  else if(command == "exit"){
    return exitHandling();
  }
  else return false;
}

void CommandLineInterface::helpHandling(){
  puts("start - starts everything");
  puts("start server - creates socket and bind ip and port");
  puts("start listening - set server to passive mode");
  puts("start waiting  - start waiting on select");
  puts("stop - obvious");
  puts("stop waiting - stop waiting on select");
  puts("set port NUMBER_OF_PORT - obvious");
  puts("set connections NUMBER_OF_CONNECTIONS - set max number of connections");
  puts("close NUMBER_OF_SOCKET - obvious");
  puts("add user user_name user_password");
  puts("add group group_name admin_name");
  puts("delete user user_name");
  puts("delete group group_name");
  puts("closebylogin CLIENT_LOGIN - obvious");
}

bool CommandLineInterface::startHandling(std::vector<std::string> splitedCommand){
  if(!splitedCommand.size()){
    fullStartHandling();
    return true;
  }
  else if(splitedCommand[0] == "server"){
    startServerHandling();
    return true;
  }
  else if(splitedCommand[0] == "listening"){
    startListeningHandling();
    return true;
  }
  else if(splitedCommand[0] == "waiting"){
    startWaitingHandling();
    return true;
  }
  else return false;
}

bool CommandLineInterface::stopHandling(std::vector<std::string> splitedCommand){
  if(!splitedCommand.size()){
    fullStopHandling();
    return true;
  }
  else if(splitedCommand[0] == "waiting"){
    stopWaitingHandling();
    return true;
  }
  else return false;
}

bool CommandLineInterface::setHandling(std::vector<std::string> splitedCommand){
  if(splitedCommand.size()<2) return false;
  auto it = splitedCommand.begin(); it++;
  if( !checkIfStringIsNumber(*it)) return false;
  if(splitedCommand[0] == "port"){
    setPortHandling( std::stoi(splitedCommand[1]) );
    return true;
  }
  else if(splitedCommand[0] == "connections"){
    setMaxConnectionsHandling(std::stoi(splitedCommand[1]));
    return true;
  }
  else return false;
}

bool CommandLineInterface::closeHandling(std::vector<std::string> splitedCommand){
  if(!splitedCommand.size()) return false;
  if( !checkIfStringIsNumber(splitedCommand[0]) ) return false;
  int result = Network::closeSocketWithBlocking(std::stoi(splitedCommand[0]));
  if(result == 1){
    puts("Cannot close server socket");
    return true;
  }
  else if(result == 2){
    puts("Socket doesnt exist");
    return true;
  }
  else{
    puts("Socket closed");
    return true;
  }
}

bool CommandLineInterface::addHandling(std::vector<std::string> splitedCommand){
  if(splitedCommand.size() < 3) return false;
  if(splitedCommand[0] == "user"){
    addUserHandling(splitedCommand[1] , splitedCommand[2]);
    return true;
  }
  else if(splitedCommand[0] == "group"){
    addGroupHandling(splitedCommand[1] , splitedCommand[2]);
    return true;
  }
  else return false;
}

bool CommandLineInterface::deleteHandling(std::vector<std::string> splitedCommand){
  if(splitedCommand.size() < 2) return false;
  if(splitedCommand[0] == "user"){
    deleteUserHandling(splitedCommand[1]);
    return true;
  }
  else if(splitedCommand[0] == "group"){
    deleteGroupHandling(splitedCommand[1]);
    return true;
  }
  else return false;
}

void CommandLineInterface::fullStartHandling(){
  startServerHandling();
  startListeningHandling();
  startWaitingHandling();
}

void CommandLineInterface::startServerHandling(){
  if(Network::ServerOperation::getIsSocketNumberSet()) {
    puts("Server already started!");
    return;
  }
  //czy sie udalo stworzyc
  if(Network::startServer() == -1){
    puts("Cannot start server!");
    return;
  }
}

void CommandLineInterface::startListeningHandling(){
  if(!Network::ServerOperation::getIsSocketNumberSet()) {
    puts("Server not started!");
    return;
  }
  //Czy juz jest pasywny
  if(Network::ServerOperation::getIsSocketListening()){
    puts("Socket already passive!");
    return;
  }
  //czy udalo sie
  if(Network::ServerOperation::listenServerSocket() == -1){
    puts("Cannot set passive mode!");
  }
}

void CommandLineInterface::startWaitingHandling(){
  if(!Network::ServerOperation::getIsSocketListening()){
    puts("Socket not passive!");
    return;
  }
  //czy moze juz server nasluchuje
  if(Network::isServerWaiting()){
    puts("Socket already waiting!");
    return;
  }
  //no to tworzymy watek
  puts("Server is waiting on socket!");
  pthread_t selectThread;
  pthread_create(&selectThread, NULL, &CommandLineInterface::selectThreadWrapper, this);
}

void CommandLineInterface::fullStopHandling(){
  //czy stworzono socket
  if(!Network::ServerOperation::getIsSocketNumberSet()) {
    puts("Server not started!");
    return;
  }
  //jak stworzono to go zamykamy i wszystkich klientow
  Network::closeServer();
}

void CommandLineInterface::stopWaitingHandling(){
  //czy server nasluchuje
  if(!Network::isServerWaiting()){
    puts("Server not started!");
    return;
  }
  //jesli tak to wstrzymujemy nasluchiwanie ale klientow zatrzymujemy
  Network::stopWaiting();
}

void CommandLineInterface::setPortHandling(int port){
  if(Network::ServerOperation::getIsSocketNumberSet()) {
    puts("Cannot set port while server working!");
    return;
  }
  //sprawdzamy jaka to liczba
  if(port > 65535 || port < 49152 ){
    puts("Incorrect port number!");
    return;
  }
  std::cout<<"New port number is:"<<port<<std::endl;
  Network::ServerOperation::setPort(port);
}

void CommandLineInterface::setMaxConnectionsHandling(int connections){
  if(Network::ServerOperation::getIsSocketNumberSet()) {
    puts("Cannot set maxconnections while server working!");
    return;
  }
  //sprawdzamy jaka to liczba
  if(connections < 0  || connections > 1023 ){
    puts("Incorrect connections number");
    return;
  }
  std::cout<<"New connections number is:"<<connections<<std::endl;
  Network::ServerOperation::setConnections(connections);
}

void CommandLineInterface::addUserHandling(std::string login, std::string password){
  std::hash<std::string> hasher;
  std::string hashedPassword = std::to_string( hasher(password) );
  if(MessageHandler::DataBaseConnector::rootAddUser(login , hashedPassword) == -1){
    puts("Login already in use!");
    return;
  }
  puts("User created");
}

void CommandLineInterface::addGroupHandling(std::string groupName, std::string adminLogin){
  int result = MessageHandler::DataBaseConnector::rootAddGroup(groupName, adminLogin);
  if(result == -1){
    puts("User passed as admin doesn't exist!");
    return;
  }
  else if(result == -2){
    puts("Group already exist!");
    return;
  }
  puts("Group created");
}

void CommandLineInterface::deleteUserHandling(std::string login){
  if(MessageHandler::DataBaseConnector::rootDeleteUser(login) == -1){
    puts("User doesn't exist!");
    return;
  }
  puts("User deleted!");
}

void CommandLineInterface::deleteGroupHandling(std::string groupName){
  if(MessageHandler::DataBaseConnector::rootDeleteGroup(groupName) == -1){
    puts("Group doesn't exist!");
    return;
  }
  puts("Group deleted!");
}

bool CommandLineInterface::exitHandling(){
  fullStopHandling();
  MessageHandler::stopLoop();
  this->working=false;
  puts("BYEBYE :)");
  return true;
}

bool CommandLineInterface::checkIfStringIsNumber(std::string toCheck){
  for(auto it = toCheck.begin() ; it != toCheck.end() ; it++){
    if(!std::isdigit(*it)) return false;
  }
  return true;
}

void * CommandLineInterface::selectThreadWrapper(void * Object){
  ((CommandLineInterface *)Object)->Network::waitForSignal();
}

void * CommandLineInterface::logicThreadWrapper(void * Object){
  ((CommandLineInterface *)Object)->MessageHandler::LogicThreadLoop();
}
