#include "RoomManager.h"

#include "CommunicationException.h"


/**
 * \brief Creates a new room.
 * \param user The owner.
 * \param data The room's metadata.
 */
unsigned RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	if (m_rooms.find(data.id) != m_rooms.end())
	{
		throw CommunicationException("There's already a room with this name", EXSTS);
	}
	std::lock_guard<std::mutex> lock(m_roomMutex);
	Room room(user, data);
	m_rooms.insert_or_assign(data.id, room);
	return m_last_id++;
}

/**
 * \brief Deletes a room.
 * \param id The room's id.
 */
void RoomManager::deleteRoom(unsigned id)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	if (m_rooms.find(id) != m_rooms.end())
	{
		m_rooms.erase(id);
		return;
	}
	throw CommunicationException("Room doesn't exist", DSNT_EXST);
}

/**
 * \brief I do not know either.
 * \param id The room's id.
 * \return I do not know.
 */
unsigned RoomManager::getRoomState(unsigned id)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	if (m_rooms.find(id) != m_rooms.end())
	{
		return m_rooms.at(id).getRoomData().isActive;
	}
	throw CommunicationException("Room doesn't exist", DSNT_EXST);
}

/**
 * \brief Gets the data of all of the rooms.
 * \return All of the rooms' metadata.
 */
std::vector<RoomData> RoomManager::getRooms()
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
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
std::map<unsigned, Room> RoomManager::getAllRooms()
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	return m_rooms;
}

void RoomManager::addPlayerToRoom(const LoggedUser& user, int id)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	if (m_rooms.find(id) != m_rooms.end())
	{
		m_rooms.at(id).addUser(user);
		return;
	}
	throw CommunicationException("Room doesn't exist", DSNT_EXST);
}

unsigned RoomManager::getLastId() const
{
	return m_last_id;
}
