#pragma once

#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "Singleton.h"

class LoginRequestHandler;

class RequestHandlerFactory : public Singleton<RequestHandlerFactory>
{	
public:
	LoginRequestHandler createLoginRequestHandler();
	
private:
	RequestHandlerFactory();

	friend class Singleton;
};
