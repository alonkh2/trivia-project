#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id >= SO_CD && info.id <= CR_CD;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info)
{
	switch (info.id)
	{
	case SO_CD:
		return signout(info);
	case GR_CD:
		return getRooms(info);
	case GPR_CD:
		return getPlayersInRoom(info);
	case GPS_CD:
		return getPersonalStats(info);
	case GHS_CD:
		return getHighScore(info);
	case JR_CD:
		return joinRoom(info);
	case CR_CD:
		return createRoom(info);
	default:
		RequestResult rr;
		rr.newHandler = nullptr;
		return rr;
	}
}

RequestResult MenuRequestHandler::signout(const RequestInfo& info)
{
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& info)
{
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& info)
{
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info)
{
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info)
{
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info)
{
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& info)
{
}
