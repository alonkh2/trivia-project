#include "MenuRequestHandler.h"

#include <utility>


#include "JsonResponsePacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager,
                                       StatisticsManager& statisticsManager,
                                       RequestHandlerFactory& handlerFactory, LoginManager& loginManager) :
	m_user(std::move(user)),
	m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory),
	m_loginManager(loginManager)
{
}

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

RequestResult MenuRequestHandler::signout(const RequestInfo& info) const
{
	RequestResult rr;
	LogoutResponse lr;
	rr.newHandler = nullptr;
	try
	{
		m_loginManager.logout(m_user.getUsername());
		lr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lr);
		rr.newHandler = nullptr;
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		if (e.getStatus() == NT_LGD)
		{
			rr.newHandler = m_handlerFactory.createLoginRequestHandler();
		}
		else
		{
			rr.newHandler = m_handlerFactory.createMenuRequestHandler();
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return rr;
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
