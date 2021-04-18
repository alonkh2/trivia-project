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
