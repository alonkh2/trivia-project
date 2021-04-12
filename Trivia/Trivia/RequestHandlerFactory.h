#pragma once

#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"


class RequestHandlerFactory
{
public:
	LoginRequestHandler createLoginRequestHandler();
};
