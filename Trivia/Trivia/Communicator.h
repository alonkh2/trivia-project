#pragma once

#include <map>

#include <iostream>
#include <mutex>

#include "IRequestHandler.h"
#include "WinSock2.h"
#include "Windows.h"
#include "constants.h"
#include <thread>
#include <unordered_map>


#include "Singleton.h"

class RequestHandlerFactory;

class Communicator : public Singleton<Communicator>
{
public:
	// D'tor
	~Communicator();

	// Server starter.
	void startHandleRequests();

private:
	// C'tor. Private because of singleton template 
	Communicator(RequestHandlerFactory& handlerFactory);

	// Server functions 
	void bindAndListen();
	void handleNewClient(SOCKET client);

	void sendall(SOCKET socket, const std::vector<Byte>& msg) const;
	char* receive(SOCKET socket, int numOfBytes, int flags = 0) const;
	
	SOCKET m_serverSocket;
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	std::mutex m_clientMutex;

	friend class Singleton;
};
