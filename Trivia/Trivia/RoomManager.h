#pragma once

#include <map>
#include <mutex>


#include "Singleton.h"
#include "Room.h"
#include "IDatabase.h"

class RoomManager : public Singleton<RoomManager>
{
public:
	~RoomManager() = default;

	unsigned createRoom(const LoggedUser& user, const RoomData& data);
	void deleteRoom(unsigned id);
	void closeRoom(unsigned id);
	unsigned getRoomState(unsigned id);
	std::vector<RoomData> getRooms();
	std::vector<RoomData> getNotActiveRooms();
	std::map<unsigned, Room> getAllRooms();

	Room& getRoom(unsigned id);

	void addPlayerToRoom(const LoggedUser& user, int id);

	unsigned getLastId() const;
private:
	RoomManager(IDatabase& database): m_last_id(100), m_database(database) {}
	
	std::map<unsigned, Room> m_rooms;
	unsigned m_last_id;
	IDatabase& m_database;

	std::mutex m_roomMutex;

	friend class Singleton;
};
