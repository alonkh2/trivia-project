#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager) : m_handlerFactory(handlerFactory), m_loginManager(loginManager)
{
}

/**
 * \brief Checks if a request is a login/signup request.
 * \param info The request's info.
 * \return True if the request is a login/signup request, else false.
 */
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	// going to change this once i add constants
	return info.id == 129 || info.id == 130;
}

/**
 * \brief Handles a request. Does nothing for now.
 * \param info The request's info.
 * \return The result of the request.
 */
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info)
{
	RequestResult rr;
	strcpy_s(rr.buffer, "hello world");
	rr.newHandler = nullptr;
	return rr;
}

/**
 * \brief Performs a login attempt. Does nothing for now. 
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult LoginRequestHandler::login(const RequestInfo& info)
{

	RequestResult rr;
	rr.newHandler = nullptr;
	return rr;
}

/**
 * \brief Performs a signup attempt. Does nothing for now. 
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
	RequestResult rr;
	rr.newHandler = nullptr;
	return rr;
}
