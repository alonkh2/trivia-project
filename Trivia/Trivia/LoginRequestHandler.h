#pragma once

#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

// class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult login(const RequestInfo& info);
	RequestResult signup(const RequestInfo& info);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};
