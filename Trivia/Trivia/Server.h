#pragma once
#include "Communicator.h"
#include "IDatabase.h"

class my_class
{
public:
	void run();

private:
	IDatabase* m_database;
	Communicator m_communicator;
	RequestHandlerFactory& m_handlerFactory;
};
