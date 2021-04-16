#pragma once

#include "Singleton.h"
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server : public Singleton<Server>
{
public:
	// Functions and methods
	void run() const;

private:
	// C'tor. Private because of singleton.
	Server();
	
	IDatabase* m_database;
	RequestHandlerFactory& m_handlerFactory;

	Communicator& m_communicator;
	
	friend class Singleton;
};
