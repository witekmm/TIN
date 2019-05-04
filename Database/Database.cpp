#include <iostream>
#include <sstream>
#include "Database.h"

Database::Database() 
	: Database(URL, DB, USER, PASSWORD){}

Database::Database(const std::string url_, const std::string db_, const std::string user_, const std::string pass_) : url(url_), db(db_), user(user_), password(pass_) 
{
	try
    {
        driver = get_driver_instance();
        con = driver->connect(url, user, password);
        con->setSchema(db);
    }
    catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        exit(0);
	}
	std::cout<<"Connected"<<std::endl;
}

Database::~Database()
{
	delete res;
	delete pstmt;
	//delete stmt;
	delete con;
}

bool Database::userInGroup(std::string groupName, std::string login)
{
	try
    {
		sql::SQLString query = "SELECT us.id, us.password from `User` AS us ";
					query+= "JOIN `User_Group` AS ug ON us.id = ug.user_id ";
					query+= "JOIN `Group` AS g ON g.id = ug.group_id ";
					query+= "WHERE g.name = ? AND us.login = ? ";

		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		pstmt->setString(2, login);
		res = pstmt->executeQuery();
				
		if(res->next())
			return true;

		return false;	
	}
    catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        exit(0);
	}
}

bool Database::groupNameExists(std::string groupName)
{
	sql::SQLString query = "SELECT g.id from `Group` AS g ";
				   query+= "WHERE g.name = ?";

	pstmt = con->prepareStatement(query);
	pstmt->setString(1, groupName);
	res = pstmt->executeQuery();
				
	if(res->next())
		return true;
	return false;	
}

void Database::createGroup(std::string groupName, int userId)
{
	sql::SQLString query = "INSERT INTO `Group` VALUES (0,?,?)";

	pstmt = con->prepareStatement(query);
	pstmt->setString(1, groupName);
	pstmt->setInt(2, userId);
	pstmt->execute();
}

bool Database::isAdministrator(std::string groupName, int userId)
{
	sql::SQLString query = "SELECT g.id from `Group` AS g ";
				   query+= "WHERE g.name = ? AND g.leader = ?";

	pstmt = con->prepareStatement(query);
	pstmt->setString(1, groupName);
	pstmt->setInt(2, userId);
	res = pstmt->executeQuery();
				
	if(res->next())
		return true;
	return false;
}

void Database::deleteGroup(std::string groupName)
{
	sql::SQLString query = "DELETE FROM `Group` WHERE name=?";

	pstmt = con->prepareStatement(query);
	pstmt->setString(1, groupName);
	//int updated = 0;
	//updated += pstmt->executeUpdate();
	//std::cout<<"updated: "<<updated<<std::endl;
	pstmt->execute();
}

int Database::getUserId(std::string login)
{
	sql::SQLString query = "SELECT id FROM `User` WHERE login=?";
	pstmt = con->prepareStatement(query);
	pstmt->setString(1, login);
	res = pstmt->executeQuery();

	if(res->next())
		return res->getInt("id");
	else
	{
		std::cout<<"No user with login: "<<login<<std::endl;
		return -1;
	}
}

int Database::getGroupId(std::string groupName)
{
	sql::SQLString query = "SELECT id FROM `Group` WHERE name=?";
	pstmt = con->prepareStatement(query);
	pstmt->setString(1, groupName);
	res = pstmt->executeQuery();

	if(res->next())
		return res->getInt("id");
	else
	{
		std::cout<<"No group with name: "<<groupName<<std::endl;
		return -1;
	}
}

bool Database::belongToGroup(std::string groupName, std::string login)
{
	return belongToGroup(groupName, getUserId(login));
}

bool Database::belongToGroup(std::string groupName, int userId)
{
	sql::SQLString query = "SELECT * from `User_Group` AS ug ";
				   query+= "JOIN `Group` AS g ON ug.group_id = g.id ";
				   query+= "WHERE g.name = ? AND ug.user_id = ?";

	pstmt = con->prepareStatement(query);
	pstmt->setString(1, groupName);
	pstmt->setInt(2, userId);
	res = pstmt->executeQuery();
				
	if(res->next())
		return true;
	return false;
}

void Database::addUserToGroup(std::string groupName, std::string login)
{
	addUserToGroup(groupName, getUserId(login));
}

void Database::addUserToGroup(std::string groupName, int userId)
{
	sql::SQLString query = "INSERT INTO `User_Group` VALUES (?,?)";

	pstmt = con->prepareStatement(query);
	pstmt->setInt(1, userId);
	pstmt->setInt(2, getGroupId(groupName));
	pstmt->execute();
}

std::string Database::getUserPassword(std::string login)
{
	sql::SQLString query = "SELECT password FROM `User` WHERE login=?";
	pstmt = con->prepareStatement(query);
	pstmt->setString(1, login);
	res = pstmt->executeQuery();

	if(res->next())
		return res->getString("password");
	else
	{
		std::cout<<"No user with login: "<<login<<std::endl;
		return "";
	}
}

//bool Database::isUser()
