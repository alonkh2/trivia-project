#pragma once
#include <string>

class LoggedUser
{
public:
	// C'tor
	LoggedUser(std::string username);

	// Getters and setters
	std::string getUsername() const;
	
private:
	std::string m_username;
};
