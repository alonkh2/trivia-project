#pragma once
#include <iostream>

#include "Singleton.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"


class LoginRequestHandler;

class RequestHandlerFactory : public Singleton<RequestHandlerFactory>
{	
public:
	LoginRequestHandler createLoginRequestHandler();
	
private:
	RequestHandlerFactory(IDatabase& db);

	friend class Singleton;
};
