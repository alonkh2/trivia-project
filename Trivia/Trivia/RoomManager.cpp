#include "RoomManager.h"


/**
 * \brief Creates a new room.
 * \param user The owner.
 * \param data The room's metadata.
 */
void RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	if (m_rooms.find(data.id) != m_rooms.end())
	{
		throw std::exception("There's already a room with this name! ");
	}
	Room room(user, data);
	m_rooms.insert_or_assign(data.id, room);
}

/**
 * \brief Deletes a room.
 * \param id The room's id.
 */
void RoomManager::deleteRoom(unsigned id)
{
	if (m_rooms.find(id) != m_rooms.end())
	{
		m_rooms.erase(id);
		return;
	}
	throw std::exception("There's no such room! ");
}

/**
 * \brief I do not know either.
 * \param id The room's id.
 * \return I do not know.
 */
unsigned RoomManager::getRoomState(unsigned id)
{
	if (m_rooms.find(id) != m_rooms.end())
	{
		return m_rooms.at(id).getRoomData().isActive;
	}
	throw std::exception("There's no such room! ");
}

/**
 * \brief Gets the data of all of the rooms.
 * \return All of the rooms' metadata.
 */
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (const auto& room : m_rooms)
	{
		rooms.push_back(room.second.getRoomData());
	}
	return rooms;
}

/**
 * \brief I do not know.
 * \return I do not know.
 */
std::map<unsigned, Room> RoomManager::getAllRooms() const
{
	return m_rooms;
}
