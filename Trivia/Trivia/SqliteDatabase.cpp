#include "SqliteDatabase.h"

/*
* This function returns the ID parameter of all tables
*/
int getStringCallback(void* used, int argc, char** argv, char** az_col_name)
{
	std::string* val = static_cast<std::string*>(used);
	if (argc > 0)
	{
		*val = atoi(argv[0]);
	}

	return 0;
}

bool SqliteDatabase::execCommand(const std::string command, int (*foo)(void*, int, char**, char**), std::string* ansRef)
{
	int res = sqlite3_exec(_db, command.c_str(), foo, &ansRef, nullptr);

	return res == SQLITE_OK;
}

SqliteDatabase::SqliteDatabase()
{
	std::string dbName = "triviaDB.sqlite";
	sqlite3_open(dbName.c_str(), &_db);
	std::string createTableQuery = "CREATE TABLE IF NOT EXISTS USERS (username TEXT PRIMARY KEY, password TEXT, email TEXT);";
	 
	execCommand(createTableQuery, nullptr, nullptr);
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
}

bool SqliteDatabase::doesUserExist(const std::string& username)
{
	std::string sqlQuery = "SELECT username FROM USERS WHERE username = '" + username + "';";
	std::string dbResp;

	execCommand(sqlQuery, getStringCallback, &dbResp);

	return dbResp == username ? true : false;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string dbResp;
	std::string passwordQuery = "SELECT password FROM USERS WHERE username = '" + username + "';";

	if (!doesUserExist(username))
	{
		std::string errMsg = "User: " + username + " does not exist!";
		throw std::exception(errMsg.c_str());
	}
	execCommand(passwordQuery, getStringCallback, &dbResp);
	
	return dbResp == password;
}

void SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	std::string addUserQuery = "INSERT INTO USERS (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "');";

	if (doesUserExist(username))
	{
		std::string errMsg = "User: " + username + " already exists!";
		throw std::exception(errMsg.c_str());
	}

	execCommand(addUserQuery, nullptr, nullptr);
}