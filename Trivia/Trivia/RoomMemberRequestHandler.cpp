#include "RoomMemberRequestHandler.h"

#include <utility>


/**
 * \brief Handles a getRoomState request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info) const
{
	RequestResult rr;
	GetRoomStateResponse rs;
	rr.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_room, m_user);

	try
	{
		rs.players = m_room.getAllUsers();
		rs.answerTimeout = m_room.getRoomData().timePerQuestion;
		rs.state = m_room.getRoomData().isActive;
		rs.questionCount = m_room.getRoomData().numOfQuestions;
		rs.status.push_back('1');

		if (rs.state == 2)
		{
			auto& game = m_handlerFactory.getGameManager().createGame(m_room);
			rr.newHandler = m_handlerFactory.createGameRequestHandler(game, m_user);
		}
		
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
RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info)
{
	switch (info.id)
	{
	case LR_CD:
		return leaveRoom(info);
	case GRS_CD:
		return getRoomState(info);
	default:
		return RequestResult{};
	}
}

/**
 * \brief Checks if a request is relevant.
 * \param info The request's info.
 * \return True if it's relevant, else false.
 */
bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id == LR_CD || info.id == GRS_CD;
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info) const
{
	RequestResult rr;
	LeaveRoomResponse lr;

	try
	{
		m_room.removeUser(m_user);
		m_roomManager.deleteRoom(m_room.getRoomData().id);

		lr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lr);
		rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
		rr.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_room, m_user);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}

	return rr;
}

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser user,
	RequestHandlerFactory& handlerFactory): m_room(room), m_user(std::move(user)), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}
