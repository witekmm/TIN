#ifndef DATABASE_H_
#define DATABASE_H_

#include "mysql-cppconn-8/jdbc/mysql_connection.h"
#include <mysql-cppconn-8/jdbc/cppconn/driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/exception.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include <string>

#define URL "sql.serwer1973447.home.pl"
#define USER "29773530_tin"
#define PASSWORD "TIN_2019"
#define DB "29773530_tin"

class Database {

  public:

    Database();
    Database(const std::string url, const std::string database, const std::string username, const std::string password);

    ~Database();

    void connect();
    bool userInGroup(std::string groupName, std::string login);
    void addMsgToGroup(std::string groupName, std::string text);
    bool groupNameExists(std::string groupName);
    void createGroup(std::string groupName, int userId);
    bool isAdministrator(std::string groupName, int userId);
    void deleteGroup(std::string groupName);
    bool belongToGroup(std::string groupName, std::string login);
    bool belongToGroup(std::string groupName, int userId);
    int getUserId(std::string login);
    int getGroupId(std::string groupName);
    void addUserToGroup(std::string groupName, std::string login);
    void addUserToGroup(std::string groupName, int userId);
    std::string getUserPassword(std::string login);
    bool isUser(std::string login);
    void addUserPassword(std::string login);

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

#endif /* DATABASE_H_ */
