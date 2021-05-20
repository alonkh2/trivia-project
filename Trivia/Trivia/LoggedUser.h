#pragma once
#include <string>

class LoggedUser
{
public:
	// C'tor
	LoggedUser(std::string username);

	// Getters and setters
	std::string getUsername() const;


	friend bool operator==(const LoggedUser& lhs, const LoggedUser& rhs);

	friend bool operator!=(const LoggedUser& lhs, const LoggedUser& rhs);

private:
	std::string m_username;
};
