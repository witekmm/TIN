#include "DataBaseConnector.h"

DataBaseConnector::DataBaseConnector()
    : database(){}

void sendGroupMessage(std::string content, std::string groupName, std::string login)
{
    database.addMsgToGroup(groupName, login, 1, content);
}
void createGroup(std::string groupName, std::string login)
{
    database.createGroup(groupName, login);
}
void deleteGroup(std::string groupName, std::string login)
{
    database.deleteGroup(groupName);
}
void requestToGroup(std::string groupName, std::string login)
{
    database.addUserToGroup(groupName, login);
}
void acceptRequest(std::string groupName, std::string userName, std::string login)
{
    //?? userName
}
void declineRequest(std::string groupName, std::string userName, std::string login)
{

}
void leaveGroup(std::string groupName, std::string login)
{
    database.removeUserFromGroup(groupName, login);
}
void logInUser(std::string login, std::string password, int ID)
{

}
void registerUser(std::string login, std::string password, int ID)
{
    database.addUser(login, password);
}

void checkIfMessageExistAndSend(std::string login)
{

}

int rootDeleteGroup(std::string groupName)
{
    database.deleteGroup(groupName);
}
int rootDeleteUser(std::string login)
{
    database.deleteUser(login);
}
int rootAddUser(std::string login, std::string password)
{

}
int rootAddGroup(std::string groupName, std::string administrator)
{
    database.createGroup(groupName, administrator);
}
