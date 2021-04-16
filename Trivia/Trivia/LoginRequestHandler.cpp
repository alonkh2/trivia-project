#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager) : m_handlerFactory(handlerFactory), m_loginManager(loginManager)
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	// going to change this once i add constants
	return info.id == 129 || info.id == 130;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info)
{
	RequestResult rr;
	strcpy_s(rr.buffer, "hello world");
	rr.newHandler = nullptr;
	return rr;
}

RequestResult LoginRequestHandler::login(const RequestInfo& info)
{

	RequestResult rr;
	rr.newHandler = nullptr;
	return rr;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
	RequestResult rr;
	rr.newHandler = nullptr;
	return rr;
}
