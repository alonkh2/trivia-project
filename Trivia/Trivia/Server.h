#pragma once
#include "Communicator.h"
#include "Singleton.h"
#include "IDatabase.h"

class Server : public Singleton<Server>
{
public:
	void run();

private:
	
	IDatabase* m_database;
	Communicator m_communicator;
	RequestHandlerFactory& m_handlerFactory;

	friend class Singleton;
};
