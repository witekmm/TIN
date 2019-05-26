#include "Database.h"

Database::Database()
	: Database(URL, DB, USER, PASSWORD){}

Database::Database(const std::string url_, const std::string db_, const std::string user_, const std::string pass_)
	: url(url_), db(db_), user(user_), password(pass_)
{
	try
    {
        driver = get_driver_instance();
        con = driver->connect(url, user, password);
        con->setSchema(db);
    }
    catch (sql::SQLException &e) {
		manageException(e);
	}
	std::cout<<"Connected"<<std::endl;
}

Database::~Database()
{
	delete res;
	delete pstmt;
	delete con;
}

void Database::manageException(sql::SQLException &e)
{
	std::cout << "# ERR: SQLException in " << __FILE__;
	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	std::cout << "# ERR: " << e.what();
	std::cout << " (MySQL error code: " << e.getErrorCode();
	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
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
	}
  catch (sql::SQLException &e) {
		manageException(e);
	}
	return false;
}

int Database::getGroupId(std::string groupName)
{
	try
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
		}
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return -1;
}

std::string Database::getGroupName(int groupId)
{
	try
	{
		sql::SQLString query = "SELECT name FROM `Group` WHERE id = ?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, groupId);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getString("name");
		else
		{
			std::cout<<"No group with id: "<<groupId<<std::endl;
		}
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return "";
}

bool Database::isGroup(std::string groupName)
{
	return getGroupId(groupName) != -1 ? true : false;
}

void Database::createGroup(std::string groupName, std::string login)
{
	return createGroup(groupName, getUserId(login));
}

void Database::createGroup(std::string groupName, int userId)
{
	try
	{
		sql::SQLString query = "INSERT INTO `Group` VALUES (0,?,?)";
		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		pstmt->setInt(2, userId);
		pstmt->execute();
		// add the leader as user to group as well
		addUserToGroup(groupName, userId);
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::deleteGroup(std::string groupName)
{
	try
	{
		// remove all references in User_Group
		removeAllUsersFromGroup(groupName);

		sql::SQLString query = "DELETE FROM `Group` WHERE name=?";
		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		//int updated = 0;
		//updated += pstmt->executeUpdate();
		//std::cout<<"updated: "<<updated<<std::endl;
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

bool Database::isAdministrator(std::string groupName, int userId)
{
	try
	{
		sql::SQLString query = "SELECT g.id from `Group` AS g ";
					   query+= "WHERE g.name = ? AND g.leader = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		pstmt->setInt(2, userId);
		res = pstmt->executeQuery();

		if(res->next())
			return true;
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return false;
}

void Database::changeAdministrator(std::string groupName, int userId)
{
	try
	{
		sql::SQLString query = "UPDATE `Group` SET leader = ? ";
					   query+= "WHERE name = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->setString(2, groupName);
		pstmt->executeUpdate();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

int Database::getUserId(std::string login)
{
	try
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
		}
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return -1;
}

std::string Database::getUserLogin(int userId)
{
	try
	{
		sql::SQLString query = "SELECT login FROM `User` WHERE id=?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getString("login");
		else
		{
			std::cout<<"No user with id: "<<userId<<std::endl;
		}
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return "";
}

bool Database::belongsToGroup(std::string groupName, std::string login)
{
	return belongsToGroup(groupName, getUserId(login));
}

bool Database::belongsToGroup(std::string groupName, int userId)
{
	try
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
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return false;
}

void Database::addUserToGroup(std::string groupName, std::string login)
{
	addUserToGroup(groupName, getUserId(login));
}

void Database::addUserToGroup(std::string groupName, int userId)
{
	try
	{
		sql::SQLString query = "INSERT INTO `User_Group` VALUES (?,?)";
		int groupId = getGroupId(groupName);
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->setInt(2, groupId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::removeUserFromGroup(std::string groupName, std::string login)
{
	removeUserFromGroup(groupName, getUserId(login));
}

void Database::removeUserFromGroup(std::string groupName, int userId)
{
	try
	{
		sql::SQLString query = "DELETE FROM `User_Group` WHERE user_id = ? AND group_id = ?";
		int groupId = getGroupId(groupName);
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->setInt(2, groupId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

bool Database::isUser(std::string login)
{
	return getUserId(login) != -1 ? true : false;
}

void Database::addUser(std::string login, std::string password)
{
	try
	{
		sql::SQLString query = "INSERT INTO `User` VALUES (0,?,?)";
		pstmt = con->prepareStatement(query);
		pstmt->setString(1, login);
		pstmt->setString(2, password);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::deleteUser(std::string login)
{
	deleteUser(getUserId(login));
}

void Database::deleteUser(int userId)
{
	removeAllForUser(userId);
	try
	{
		sql::SQLString query = "DELETE FROM `User` WHERE id=?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

std::string Database::getUserPassword(std::string login)
{
	try
	{
		sql::SQLString query = "SELECT password FROM `User` WHERE login=?";
		pstmt = con->prepareStatement(query);
		pstmt->setString(1, login);
		res = pstmt->executeQuery();
		if(res->next())
			return res->getString("password");
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return "";
}

void Database::updateUserPassword(std::string login, std::string newPassword)
{
	try
	{
		sql::SQLString query = "UPDATE `User` SET password = ? ";
					query+= "WHERE login = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setString(1, newPassword);
		pstmt->setString(2, login);
		pstmt->executeUpdate();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::removeAllForUser(int userId)
{
	removeAllMsgsForUser(userId);
	removeUserFromAllGroups(userId);
}

void Database::removeUserFromAllGroups(int userId)
{
	try
	{
		sql::SQLString query = "DELETE FROM `User_Group` WHERE user_id = ?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::removeAllUsersFromGroup(std::string groupName)
{
	try
	{
		sql::SQLString query = "DELETE FROM `User_Group` WHERE group_id = ?";
		int groupId = getGroupId(groupName);
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, groupId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::removeAllMsgsForUser(int userId)
{
	try
	{
		sql::SQLString query = "DELETE FROM `User_Message` WHERE user_id = ?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::removeAllUsersForMsg(int msgId)
{
	try
	{
		sql::SQLString query = "DELETE FROM `User_Message` WHERE message_id = ?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::addMsgToAdministrator(std::string groupName, std::string sender, int type, std::string text)
{
	try
	{
		sql::SQLString query = "SELECT leader from `Group` AS g ";
					   query+= "WHERE g.name = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		res = pstmt->executeQuery();

		int adminId;
		if(res->next())
			adminId = res->getInt("leader");

		int msgId = createMsg(groupName, sender, type, text);
		addMsgToUser(msgId, adminId);
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

int Database::createMsg(std::string groupName, std::string sender, int type, std::string text)
{
	try
	{
		sql::SQLString query = "INSERT INTO `Message` VALUES (0, NOW(),?,?,?,?); ";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, type);
		pstmt->setString(2, groupName);
		pstmt->setString(3, sender);
		pstmt->setString(4, text);
		pstmt->execute();

		// get id of inserted message
		query = "SELECT LAST_INSERT_ID() as id";
		pstmt = con->prepareStatement(query);
		res = pstmt->executeQuery();
		res->next();
		int msgId = res->getInt("id");
		return msgId;
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::addMsgToGroup(std::string groupName, std::string sender, int type, std::string text)
{
	try
	{
		int msgId = createMsg(groupName, sender, type, text);

		std::vector<int> users = getAllUsersFromGroup(groupName);
		int senderId = getUserId(sender);
		for(int i : users)
		{
			if(i != senderId)
				addMsgToUser(msgId, i);
		}
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

std::vector<int> Database::getAllUsersFromGroup(std::string groupName)
{
	std::vector<int> users;
	try
	{
		sql::SQLString query = "SELECT user_id FROM `User_Group` AS ug ";
					query+= "JOIN `Group` AS g ON ug.group_id = g.id ";
					query+= "WHERE g.name = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		res = pstmt->executeQuery();

		while(res->next())
			users.push_back(res->getInt("user_id"));
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return users;
}

std::vector<int> Database::getAllGroupsForUser(std::string login)
{
	return getAllGroupsForUser(getUserId(login));
}

std::vector<int> Database::getAllGroupsForUser(int userId)
{
	std::vector<int> groups;
	try
	{
		sql::SQLString query = "SELECT group_id FROM `User_Group` AS ug ";
										query+= "JOIN `User` AS u ON ug.user_id = u.id ";
										query+= "WHERE u.id = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		res = pstmt->executeQuery();

		while(res->next())
			groups.push_back(res->getInt("group_id"));
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return groups;
}

int Database::getOldestMsgForUser(std::string login)
{
	return getOldestMsgForUser(getUserId(login));
}

int Database::getOldestMsgForUser(int userId)
{
	try
	{
		sql::SQLString query = "SELECT m.id FROM `Message` AS m ";
										query+= "JOIN `User_Message` AS um ON m.id = um.message_id ";
										query+= "JOIN `User` AS u ON u.id = um.user_id ";
										query+= "WHERE u.id = ? ASC LIMIT 1";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getInt("id");
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return -1;
}

void Database::deleteOldestMsgForUser(std::string login)
{
	int msgId = getOldestMsgForUser(login);
	try
	{
		sql::SQLString query = "DELETE FROM `User_Message` WHERE message_id = ?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::addMsgToUser(int msgId, int userId)
{
	try
	{
		sql::SQLString query = "INSERT INTO `User_Message` VALUES (?,?)";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		pstmt->setInt(2, msgId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

void Database::deleteMsg(int msgId)
{
	// remove all references in User_Message
	removeAllUsersForMsg(msgId);
	try
	{
		sql::SQLString query = "DELETE FROM `Message` WHERE id=?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		pstmt->execute();
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
}

int Database::isMsgOfTypeForGroup(std::string groupName, std::string login, int type)
{
	try
	{
		sql::SQLString query = "SELECT id from `Message` AS m ";
					   query+= "JOIN `User_Message` AS um ON m.id = um.message_id ";
					   query+= "JOIN `User` AS u ON u.id = um.user_id ";
						 query+= "JOIN `User_Group` AS ug on u.id = ug.user_id";
						 query+= "JOIN `Group` AS g on g.id = ug.group_id";
					   query+= "WHERE g.name = ? AND g.type = ? AND u.login = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setString(1, groupName);
		pstmt->setInt(2, type);
		pstmt->setString(3, login);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getInt("id");
	}
  catch (sql::SQLException &e) {
		manageException(e);
	}
	return -1;
}

void Database::deleteMsgOfTypeForGroup(std::string groupName, std::string login, int type)
{
	int msgId = isMsgOfTypeForGroup(groupName, login, type);
	if(msgId != -1)
		deleteMsg(res->getInt("id"));
}

std::vector<int> Database::getAllMsgsForUser(std::string login)
{
	return getAllMsgsForUser(getUserId(login));
}

std::vector<int> Database::getAllMsgsForUser(int userId)
{
	std::vector<int> msgs;
	try
	{
		sql::SQLString query = "SELECT m.id FROM `Message` AS m ";
										query+= "JOIN `User_Message` AS um ON m.id = um.message_id ";
										query+= "JOIN `User` AS u ON u.id = um.user_id ";
										query+= "WHERE u.id = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		res = pstmt->executeQuery();

		while(res->next())
			msgs.push_back(res->getInt("id"));
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return msgs;
}

std::string Database::getMsgText(int msgId)
{
	try
	{
		sql::SQLString query = "SELECT text FROM `Message` WHERE id = ?";
		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		res = pstmt->executeQuery();
		if(res->next())
			return res->getString("text");
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return "";
}

bool Database::hasMsg(std::string login)
{
	return hasMsg(getUserId(login));
}

bool Database::hasMsg(int userId)
{
	try
	{
		sql::SQLString query = "SELECT * from `Message` AS m ";
					   				query+= "JOIN `User_Message` AS um ON um.message_id = m.id ";
					   				query+= "WHERE um.user_id = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, userId);
		res = pstmt->executeQuery();

		if(res->next())
			return true;
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return false;
}

int Database::getMsgType(int msgId)
{
	try
	{
		sql::SQLString query = "SELECT type from `Message` AS m ";
					   				query+= "WHERE m.id = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getInt("type");
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return -1;
}

std::string Database::getMsgSender(int msgId)
{
	try
	{
		sql::SQLString query = "SELECT sender from `Message` AS m ";
					   				query+= "WHERE m.id = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getString("sender");
	}
	catch(sql::SQLException &e) {
		manageException(e);
	}
	return "";
}

std::string Database::getMsgGroupName(int msgId)
{
	try
	{
		sql::SQLString query = "SELECT name from `Group` AS g ";
					   query+= "JOIN `User_Group` AS ug ON g.id = ug.group_id ";
					   query+= "JOIN `User` AS u ON u.id = ug.user_id ";
						 query+= "JOIN `User_Message` AS um on u.id = um.user_id";
						 query+= "JOIN `Message` AS m on m.id = um.message_id";
					   query+= "WHERE m.id = ?";

		pstmt = con->prepareStatement(query);
		pstmt->setInt(1, msgId);
		res = pstmt->executeQuery();

		if(res->next())
			return res->getString("name");
	}
  catch (sql::SQLException &e) {
		manageException(e);
	}
	return "";
}
