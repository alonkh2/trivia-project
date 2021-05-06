#pragma once
#include <map>

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult signout(const RequestInfo& info) const;
	RequestResult getRooms(const RequestInfo& info) const;
	RequestResult getPlayersInRoom(const RequestInfo& info) const;
	RequestResult getPersonalStats(const RequestInfo& info) const;
	RequestResult getHighScore(const RequestInfo& info) const;
	RequestResult joinRoom(const RequestInfo& info) const;
	RequestResult createRoom(const RequestInfo& info) const;

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;
};
