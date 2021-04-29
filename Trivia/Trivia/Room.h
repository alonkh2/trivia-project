#pragma once
#include <vector>

#include "LoggedUser.h"

typedef struct RoomData
{
	unsigned id;
	std::string name;
	unsigned maxPlayers;
	unsigned numOfQuestions;
	unsigned timePerQuestion;
	unsigned isActive;
} RoomData;

class Room
{
public:
	Room(const LoggedUser& user, RoomData data);
	~Room() = default;

	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers();

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

	std::vector<LoggedUser>::iterator getUserIterator(const LoggedUser& user);
};
