﻿#include "Server.h"

#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"

/**
 * \brief Runs the server, then listens to admin's commands on console.
 */
void Server::run() const
{
	std::thread comm(&Communicator::startHandleRequests, std::ref(m_communicator));
	comm.detach();
	auto working = true;
	while (working)
	{
		std::string com;

		std::getline(std::cin, com);
		if (com == EXIT_COM)
		{
			working = false;
		}
		
	}
}

Server::Server() : m_database(nullptr), m_handlerFactory(RequestHandlerFactory::getInstance<IDatabase&>(*m_database)), m_communicator(Communicator::getInstance<RequestHandlerFactory&>(m_handlerFactory))
{
}
