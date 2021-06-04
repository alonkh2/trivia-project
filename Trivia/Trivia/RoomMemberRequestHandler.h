#pragma once

#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, LoggedUser user, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult leaveRoom(const RequestInfo& info) const;
	RequestResult getRoomState(const RequestInfo& info) const;

	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};
