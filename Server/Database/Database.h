#ifndef DATABASE_H_
#define DATABASE_H_

#include <mysql-cppconn-8/jdbc/cppconn/driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/exception.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include "mysql-cppconn-8/jdbc/mysql_connection.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define URL "sql.serwer1973447.home.pl"
#define USER "29773530_tin"
#define PASSWORD "TIN_2019"
#define DB "29773530_tin"

class Database {

  public:

    Database();
    Database(const std::string url, const std::string database, const std::string username, const std::string password);
    ~Database();

    void manageException(sql::SQLException &e);
    // czy user w grupie
    bool userInGroup(std::string groupName, std::string login);
    // czy grupa istnieje
    bool isGroup(std::string groupName);
    int getGroupId(std::string groupName);
    std::string getGroupName(int groupId);
    // stworz grupe z podanym id administratora
    void createGroup(std::string groupName, int userId);
    void createGroup(std::string groupName, std::string login);
    // usun grupe
    void deleteGroup(std::string groupName);
    // czy userId to administrator podanej grupy
    bool isAdministrator(std::string groupName, int userId);
    // update leadera
    void changeAdministrator(std::string groupName, int userId);
    // czy nalezy do grupy
    bool belongsToGroup(std::string groupName, std::string login);
    bool belongsToGroup(std::string groupName, int userId);
    int getUserId(std::string login);
    std::string getUserLogin(int userId);
    void addUserToGroup(std::string groupName, std::string login);
    void addUserToGroup(std::string groupName, int userId);
    void removeUserFromGroup(std::string groupName, std::string login);
    void removeUserFromGroup(std::string groupName, int userId);
    // czy user istnieje
    bool isUser(std::string login);
    void addUser(std::string login, std::string password);
    void deleteUser(std::string login);
    void deleteUser(int userId);
    std::string getUserPassword(std::string login);
    void updateUserPassword(std::string login, std::string newPassword);
    // usun wszystkie połaczenia z grupa w User_Group
    void removeAllUsersFromGroup(std::string groupName);
    // usun wszystkie polaczenia usera z grupami w User_Group
    void removeUserFromAllGroups(int userId);
    // usun wszystkie polaczenia w User_Message
    void removeAllMsgsForUser(int userId);
    void removeAllUsersForMsg(int msgId);
    // po prostu za jednym wywolaniem dwa wyzej dla usera
    void removeAllForUser(int userId);

    void addMsgToAdministrator(std::string groupName, std::string sender, int type, std::string text);
    void addMsgToGroup(std::string groupName, std::string sender, int type, std::string text);
    void addMsgToUser(int msgId, int userId);
    std::vector<int> getAllUsersFromGroup(std::string groupName);
    std::vector<int> getAllGroupsForUser(std::string login);
    std::vector<int> getAllGroupsForUser(int userId);
    int getOldestMsgForUser(std::string login);
    int getOldestMsgForUser(int userId);
    std::vector<int> getAllMsgsForUser(std::string login);
    std::vector<int> getAllMsgsForUser(int userId);
    std::string getMsgText(int msgId);
    int createMsg(std::string groupName, std::string sender, int type, std::string text);
    void deleteMsg(int msgId);
    int isMsgOfTypeForGroup(std::string groupName, std::string login, int type);
    void deleteMsgOfTypeForGroup(std::string groupName, std::string login, int type);
    bool hasMsg(std::string login);
    bool hasMsg(int userId);

  private:

    std::string url;
    std::string db;
    std::string user;
    std::string password;
    sql::Driver* driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
};

#endif
