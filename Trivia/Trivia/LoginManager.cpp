#include "LoginManager.h"
#include <exception>

LoginManager::LoginManager(IDatabase& database): m_database(database)
{
}

/**
 * \brief Inserts a user's details into the database and adds them to the connected user list.
 * \param username The user's username.
 * \param password The user's password.
 * \param email The user's email.
 */
void LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	/*
	 * not anymore
	 */
	if (exists(username))
	{
		throw LoginException("User exists already!", EXSTS);
	}
	m_database.addNewUser(username, password, email);
	std::lock_guard<std::mutex> lg(m_usersMutex);
	m_logged_users.emplace_back(username);
}

/**
 * \brief Logs a user with a given username to the server.
 * \param username The user's username.
 * \param password The user's password.
 */
void LoginManager::login(const std::string& username, const std::string& password)
{
	/*
	 * Temporary, will replace with exceptions of my own.
	 */
	if (!m_database.doesUserExist(username))
	{
		throw LoginException("User doesn't exist! Please signup instead", DSNT_EXST);
	}
	if (!m_database.doesPasswordMatch(username, password))
	{
		throw LoginException("Password doesn't match! Please try again", DSNT_EXST);
	}
	if (exists(username))
	{
		throw LoginException("Username connected already!", LGD_IN);
	}
	std::lock_guard<std::mutex> lg(m_usersMutex);
	m_logged_users.emplace_back(username);
}

/**
 * \brief Logs a user out of the server.
 * \param username The user's username.
 */
void LoginManager::logout(const std::string& username)
{
	if (!exists(username))
	{
		throw LoginException("Username doesn't exist or is not connected!", DSNT_EXST);
	}
	std::lock_guard<std::mutex> lg(m_usersMutex);
	m_logged_users.erase(getUserIterator(username));
}

/**
 * \brief Checks if a user with a given username is connected to the server.
 * \param username The user's username.
 * \return True if a user with this name is connected to the server, else false.
 */
bool LoginManager::exists(const std::string& username)
{
	std::lock_guard<std::mutex> lg(m_usersMutex);
	if (!m_database.doesUserExist(username) && getUserIterator(username) == m_logged_users.end())
	{
		return false;
	}
	return true;
}

/**
 * \brief Finds a user's position in the vector.
 * \param username The user's username.
 * \return An iterator indicating the position of the user in the vector, or the end of the vector if the user doesn't exist.
 */
std::vector<LoggedUser>::iterator LoginManager::getUserIterator(const std::string& username)
{
	for (auto it = m_logged_users.begin(); it != m_logged_users.end(); ++it)
	{
		if (it->getUsername() == username)
		{
			return it;
		}
	}
	return m_logged_users.end();
}
