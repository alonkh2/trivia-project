#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketDeserializer.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(const Room& room, LoggedUser user, RequestHandlerFactory& handlerFactory);
	
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult closeRoom(const RequestInfo& info) const;
	RequestResult startGame(const RequestInfo& info);
	RequestResult getRoomState(const RequestInfo& info);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};
