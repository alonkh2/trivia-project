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

/**
 * \brief Function constructs an SqliteDatabase
 */
SqliteDatabase::SqliteDatabase()
{
	std::string dbName = "triviaDB.sqlite";
	sqlite3_open(dbName.c_str(), &_db);
	std::string createTableQuery = "CREATE TABLE IF NOT EXISTS USERS (username TEXT PRIMARY KEY, password TEXT, email TEXT);";
	 
	execCommand(createTableQuery, nullptr, nullptr);
}

/**
 * \brief Function closes the database
 */
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
}

/**
 * \brief Checks if a user exists in the database
 * \param username The user's username.
 * \return A bool indicating if a user exists in the DB.
 */
bool SqliteDatabase::doesUserExist(const std::string& username)
{
	std::string sqlQuery = "SELECT username FROM USERS WHERE username = '" + username + "';";
	std::string dbResp;

	execCommand(sqlQuery, getStringCallback, &dbResp);

	return dbResp == username ? true : false;
}

/**
 * \brief Checks if the inputted password matches the DB
 * \param username The user's username.
 * \param password The user's password.
 * \return A bool indicating if the passwords match.
 */
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

/**
 * \brief Logs a user with a given username to the server.
 * \param username The user's username.
 * \param password The user's password.
 * \param email The user's email.
 */
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