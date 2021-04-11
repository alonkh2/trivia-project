#pragma once
#include <string>
#include <vector>


#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager();
	~LoginManager();
	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);
	
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_logged_users;
};
