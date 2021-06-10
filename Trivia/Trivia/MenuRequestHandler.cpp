#include "MenuRequestHandler.h"

#include <utility>


#include "JsonResponsePacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& handlerFactory) :
	m_user(std::move(user)),
	m_roomManager(handlerFactory.getRoomManager()), m_statisticsManager(handlerFactory.getStatisticsManager()), m_handlerFactory(handlerFactory),
	m_loginManager(handlerFactory.getLoginManager())
{
}

/**
 * \brief Checks if a request is relevant.
 * \param info The request's info.
 * \return True if the request is relevant, else false.
 */
bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id >= SO_CD && info.id <= CR_CD;
}

/**
 * \brief Calls the correct function to handle the request.
 * \param info The request's info.
 * \return The request's result.
 */
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

/**
 * \brief Signs a player out.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::signout(const RequestInfo& info) const
{
	RequestResult rr{};
	LogoutResponse lr{};
	rr.newHandler = nullptr;
	try
	{
		m_loginManager.logout(m_user.getUsername());
		lr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lr);
		rr.newHandler = m_handlerFactory.createLoginRequestHandler();
		std::cout << "logged out" << std::endl;
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
			rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return rr;
}

/**
 * \brief Handles a getRooms request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::getRooms(const RequestInfo& info) const
{
	RequestResult rr{};
	GetRoomsResponse gr{};
	rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	
	try
	{
		gr.rooms = m_roomManager.getNotActiveRooms();
		gr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gr);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}
	return rr;
}

/**
 * \brief Handles a getPlayersInRoom request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& info) const
{
	GetPlayersInRoomResponse gr{};
	RequestResult rr{};
	rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	
	try
	{
		const auto data = JsonResponsePacketDeserializer::deserializeGetPlayersRequest(info.buffer);
		// gr.players = m_roomManager.getAllRooms().at(data.roomId).getAllUsers();
		m_roomManager.getRoom(data.roomId).getAllUsers();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gr);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();	
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}
	
	return rr;
}

/**
 * \brief Handles a getPersonalStats request.
 * \param info Tne request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info) const
{
	GetPersonalStatsResponse gr;
	RequestResult rr;
	rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	
	try
	{
		gr.statistics = m_statisticsManager.getStatistics(m_user.getUsername());
		gr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gr);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		rr.newHandler = nullptr;
	}

	return rr;
}

/**
 * \brief Handles a getHighScore request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info) const
{
	GetHighScoreResponse gr;
	RequestResult rr;
	rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	
	try
	{
		gr.statistics = m_statisticsManager.getHighScore();
		gr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gr);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}

	return rr;
}

/**
 * \brief Handles a joinRoom request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info) const
{
	JoinRoomResponse jr;
	RequestResult rr;

	try
	{
		const auto data = JsonResponsePacketDeserializer::deserializeJoinRoomRequest(info.buffer);
		// m_roomManager.getAllRooms().at(data.roomId).addUser(m_user);
		m_roomManager.addPlayerToRoom(m_user, data.roomId);
		
		jr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(jr);
		rr.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_roomManager.getRoom(data.roomId), m_user); // Room handler.
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}

	return rr;
}

/**
 * \brief Handles a createRoom request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult MenuRequestHandler::createRoom(const RequestInfo& info) const
{
	CreateRoomResponse cr;
	RequestResult rr;

	try
	{
		const auto data = JsonResponsePacketDeserializer::deserializeCreateRoomRequest(info.buffer);
		const RoomData rd(m_roomManager.getLastId(), data.roomName, data.maxUsers, data.questionCount, data.answerTimeout, 1);
		cr.id = m_roomManager.createRoom(m_user, rd);

		cr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(cr);
		Room& room = m_roomManager.getRoom(rd.id);
		rr.newHandler = m_handlerFactory.createRoomAdminRequestHandler(room, m_user); // room admin
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}

	return rr;
}
