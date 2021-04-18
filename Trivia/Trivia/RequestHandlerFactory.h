#pragma once
#include <iostream>

#include "Singleton.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"


class LoginRequestHandler;

class RequestHandlerFactory : public Singleton<RequestHandlerFactory>
{	
public:
	// Functions and methods
	LoginRequestHandler createLoginRequestHandler();
	
private:
	// C'tor. Private because of singleton
	RequestHandlerFactory(IDatabase& db);

	IDatabase& m_database;
	LoginManager& m_loginManager;
	
	friend class Singleton;
};
