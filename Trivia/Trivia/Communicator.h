#pragma once

#include <map>

#include <iostream>
#include "IRequestHandler.h"
#include "WinSock2.h"
#include "Windows.h"
#include "constants.h"
#include <thread>

class RequestHandlerFactory;

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	void startHandleRequests();

private:
	void bindAndListen() const;
	void handleNewClient(SOCKET client) const;

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};
