#pragma once
#include <mutex>
#include <string>
#include <vector>

#include "Singleton.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include "CommunicationException.h"


class LoginManager : public Singleton<LoginManager>
{
public:
	// Functions and methods
	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);

	std::vector<LoggedUser> getLoggedUsers();

private:

	// C'tor. Private because of singleton
	LoginManager(IDatabase& database);
	
	// A function to check if a user with this username exists in the database and the logged users list.
	bool exists(const std::string& username);

	std::vector<LoggedUser>::iterator getUserIterator(const std::string& username);
	
	IDatabase& m_database;
	std::vector<LoggedUser> m_logged_users;
	std::mutex m_usersMutex;

	friend class Singleton;
};
