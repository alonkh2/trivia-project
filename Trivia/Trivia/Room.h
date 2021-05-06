#pragma once
#include <utility>
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

	RoomData(unsigned id_, std::string name_, unsigned maxPlayers_, unsigned numOfQuestions_,
	         unsigned timePerQuestion_, unsigned isActive_) : id(id_), name(std::move(name_)), maxPlayers(maxPlayers_),
	                                                          numOfQuestions(numOfQuestions_),
	                                                          timePerQuestion(timePerQuestion_), isActive(isActive_) {}
} RoomData;

class Room
{
public:
	Room(const LoggedUser& user, RoomData data);
	~Room() = default;

	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData() const;

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

	std::vector<LoggedUser>::iterator getUserIterator(const LoggedUser& user);
};
