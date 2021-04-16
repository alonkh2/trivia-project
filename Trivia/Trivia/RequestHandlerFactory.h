#pragma once
#include <iostream>

#include "Singleton.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"


class LoginRequestHandler;

class RequestHandlerFactory : public Singleton<RequestHandlerFactory>
{	
public:
	LoginRequestHandler createLoginRequestHandler();
	
private:
	RequestHandlerFactory(IDatabase& db);

	IDatabase& m_database;
	LoginManager& m_loginManager;
	
	friend class Singleton;
};
