#pragma once
#include <string>
#include <vector>


#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager(IDatabase* database);
	~LoginManager();
	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);
	
private:
	// A function to check if a user with this username exists in the database and the logged users list.
	bool exists(const std::string& username);

	std::vector<LoggedUser>::iterator getUserIterator(const std::string& username);
	
	IDatabase* m_database;
	std::vector<LoggedUser> m_logged_users;
};
