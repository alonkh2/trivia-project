#pragma once

#include "Singleton.h"
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server : public Singleton<Server>
{
public:
	void run();

private:
	Server();
	
	IDatabase* m_database;
	RequestHandlerFactory& m_handlerFactory;

	Communicator& m_communicator;
	
	friend class Singleton;
};
