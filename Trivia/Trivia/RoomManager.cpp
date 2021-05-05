#include "RoomManager.h"


void RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	if (m_rooms.find(data.id) != m_rooms.end())
	{
		throw std::exception("There's already a room with this name! ");
	}
	Room room(user, data);
	m_rooms.insert_or_assign(data.id, room);
}

void RoomManager::deleteRoom(unsigned id)
{
	if (m_rooms.find(id) != m_rooms.end())
	{
		m_rooms.erase(id);
		return;
	}
	throw std::exception("There's no such room! ");
}

unsigned RoomManager::getRoomState(unsigned id)
{
	if (m_rooms.find(id) != m_rooms.end())
	{
		return m_rooms.at(id).getRoomData().isActive;
	}
	throw std::exception("There's no such room! ");
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (const auto& room : m_rooms)
	{
		rooms.push_back(room.second.getRoomData());
	}
	return rooms;
}

std::map<unsigned, Room> RoomManager::getAllRooms() const
{
	return m_rooms;
}
