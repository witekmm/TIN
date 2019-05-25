#include "DataBaseConnector.h"

void sendGroupMessage(std::string content, std::string groupName, std::string login){
  //Sprawdz czy uzytkownik w grupie - bool Database::userInGroup(groupName, login)
  //jesli tak to dodaj wiadomosc do bazy danych dla wszystkich uzytkownikow grupy

}
void createGroup(std::string groupName, std::string login);
void deleteGroup(std::string groupName, std::string login);
void requestToGroup(std::string groupName, std::string login);
void acceptRequest(std::string groupName, std::string userName, std::string login);
void declineRequest(std::string groupName, std::string userName, std::string login);
void leaveGroup(std::string groupName, std::string login);
void logInUser(std::string login, std::string password, int ID);
void registerUser(std::string login, std::string password, int ID);

void checkIfMessageExistAndSend(std::string login);

int rootDeleteGroup(std::string groupName);
int rootDeleteUser(std::string login);
int rootAddUser(std::string login, std::string password);
int rootAddGroup(std::string groupName, std::string administrator);
