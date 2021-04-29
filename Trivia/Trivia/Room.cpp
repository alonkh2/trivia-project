#include "Room.h"

#include <utility>


Room::Room(const LoggedUser& user, RoomData data) : m_metadata(std::move(data))
{
	m_users.push_back(user);
}

void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);
}

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

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> names;
	for (auto user : m_users)
	{
		names.push_back(user.getUsername());
	}
	return names;
}

RoomData Room::getRoomData() const
{
	return m_metadata;
}

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
