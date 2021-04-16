#pragma once

#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	// C'tor
	LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager);
	
	// Functions and methods
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	// Functions and methods.
	RequestResult login(const RequestInfo& info);
	static RequestResult signup(const RequestInfo& info);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};
