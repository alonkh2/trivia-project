#pragma once
#include <map>

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RoomManager& roomManager,
	                   StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory,
	                   LoginManager& loginManager);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult signout(const RequestInfo& info) const;
	RequestResult getRooms(const RequestInfo& info);
	RequestResult getPlayersInRoom(const RequestInfo& info);
	RequestResult getPersonalStats(const RequestInfo& info);
	RequestResult getHighScore(const RequestInfo& info);
	RequestResult joinRoom(const RequestInfo& info);
	RequestResult createRoom(const RequestInfo& info);

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;
};
