#include "LoggedUser.h"

#include <utility>

LoggedUser::LoggedUser(std::string username): m_username(std::move(username))
{
}

std::string LoggedUser::getUsername() const
{
	return m_username;
}
