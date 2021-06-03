#include "RoomAdminRequestHandler.h"

#include <utility>

RoomAdminRequestHandler::RoomAdminRequestHandler(const Room& room, LoggedUser user, RequestHandlerFactory& handlerFactory):
	m_room(room), m_user(std::move(user)), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

/**
 * \brief Handles a closeRoom request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info) const
{
	RequestResult rr;
	CloseRoomResponse cr;
	
	try
	{
		m_roomManager.deleteRoom(m_room.getRoomData().id);
		cr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(cr);
		rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
		rr.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}

	return rr;
}

/**
 * \brief Handles a getRoomState request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& info)
{
	RequestResult rr;
	GetRoomStateResponse rs;
	rr.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user);
	
	try
	{
		rs.players = m_room.getAllUsers();
		rs.answerTimeout = m_room.getRoomData().timePerQuestion;
		rs.hasGameBegun = m_room.getRoomData().isActive == 2;
		rs.questionCount = m_room.getRoomData().numOfQuestions;
		rs.status.push_back('1');

		rr.buffer = JsonResponsePacketSerializer::serializeResponse(rs);
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
 * \brief Handles a request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info)
{
	switch (info.id)
	{
	case CLR_CD:
		return closeRoom(info);
	case GRS_CD:
		return getRoomState(info);
	case SG_CD:
		return startGame(info);
	default:
		return RequestResult{};
	}
}

/**
 * \brief Checks if a request is relevant.
 * \param info The request's info.
 * \return True if the request is relevant, else false.
 */
bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id >= CLR_CD && info.id <= SG_CD;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& info)
{
	RequestResult rr;
	StartGameResponse sg;

	rr.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user);

	try
	{
		m_room.start();
		sg.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(sg);
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
