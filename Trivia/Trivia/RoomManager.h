#pragma once

#include <map>
#include <mutex>


#include "Singleton.h"
#include "Room.h"

class RoomManager : public Singleton<RoomManager>
{
public:
	~RoomManager() = default;

	unsigned createRoom(const LoggedUser& user, const RoomData& data);
	void deleteRoom(unsigned id);
	unsigned getRoomState(unsigned id);
	std::vector<RoomData> getRooms();
	std::map<unsigned, Room> getAllRooms();

	Room& getRoom(unsigned id);

	void addPlayerToRoom(const LoggedUser& user, int id);

	unsigned getLastId() const;
private:
	RoomManager(): m_last_id(100) {}
	
	std::map<unsigned, Room&> m_rooms;
	unsigned m_last_id;

	std::mutex m_roomMutex;

	friend class Singleton;
};
