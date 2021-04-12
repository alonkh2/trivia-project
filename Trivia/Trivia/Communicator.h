#pragma once

#include <map>


#include "IRequestHandler.h"
#include "WinSock2.h"
#include "Windows.h"
#include "constants.h"

class RequestHandlerFactory;

class Communicator
{
public:
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient(SOCKET client);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};
