#include "LoggedUser.h"

#include <utility>

/**
 * \brief C'tor.
 * \param username The user's username.
 */
LoggedUser::LoggedUser(std::string username): m_username(std::move(username))
{
}

/**
 * \brief Username getter.
 * \return User's username.
 */
std::string LoggedUser::getUsername() const
{
	return m_username;
}

bool operator==(const LoggedUser& lhs, const LoggedUser& rhs)
{
	return lhs.m_username == rhs.m_username;
}

bool operator!=(const LoggedUser& lhs, const LoggedUser& rhs)
{
	return !(lhs == rhs);
}
