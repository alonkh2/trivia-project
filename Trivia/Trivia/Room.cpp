#include "Room.h"

#include <utility>


Room::Room(const LoggedUser& user, RoomData data) : m_metadata(std::move(data))
{
	m_users.push_back(user);
}

/**
 * \brief Adds a new user to the room.
 * \param user The user to add.
 */
void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);
}

/**
 * \brief Removes a user from the room.
 * \param user The user to remove.
 */
void Room::removeUser(const LoggedUser& user)
{
	const auto userIterator = getUserIterator(user);
	if (userIterator != m_users.end())
	{
		m_users.erase(userIterator);
		return;
	}
	throw std::exception("No such user! ");
}

/**
 * \brief Gets the names of all of the users in the room.
 * \return All of the users in the room.
 */
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> names;
	for (const auto& user : m_users)
	{
		names.push_back(user.getUsername() + ",");
	}
	return names;
}

/**
 * \brief metadata getter.
 * \return The room's data.
 */
RoomData Room::getRoomData() const
{
	return m_metadata;
}

/**
 * \brief Gets a user's iterator.
 * \param user The user to find.
 * \return The iterator of the user.
 */
std::vector<LoggedUser>::iterator Room::getUserIterator(const LoggedUser& user)
{
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (*it == user)
		{
			return it;
		}
	}
	return m_users.end();
}
