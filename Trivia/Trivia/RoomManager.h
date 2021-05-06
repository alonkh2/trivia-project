#pragma once

#include <map>

#include "Singleton.h"
#include "Room.h"

class RoomManager : public Singleton<RoomManager>
{
public:
	~RoomManager() = default;

	void createRoom(const LoggedUser& user, const RoomData& data);
	void deleteRoom(unsigned id);
	unsigned getRoomState(unsigned id);
	std::vector<RoomData> getRooms();
	std::map<unsigned, Room> getAllRooms() const;

	
private:
	RoomManager() = default;
	
	std::map<unsigned, Room> m_rooms;

	friend class Singleton;
};
