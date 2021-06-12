#pragma once
#include <iostream>

#include "Singleton.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"


class MenuRequestHandler;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory : public Singleton<RequestHandlerFactory>
{	
public:
	// Functions and methods
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const std::string& username);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room& room, const LoggedUser& user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room& room, const LoggedUser& user);
	GameRequestHandler* createGameRequestHandler(Game& game, const LoggedUser& user);
	
	LoginManager& getLoginManager() const;
	RoomManager& getRoomManager() const;
	StatisticsManager& getStatisticsManager() const;
	
private:
	// C'tor. Private because of singleton
	RequestHandlerFactory(IDatabase& db);

	IDatabase& m_database;
	LoginManager& m_loginManager;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	
	friend class Singleton;
};
