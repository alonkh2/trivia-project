#pragma once

#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(const Room& room, const LoggedUser& user, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult leaveRoom(const RequestInfo& info);
	RequestResult getRoomState(const RequestInfo& info);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};
