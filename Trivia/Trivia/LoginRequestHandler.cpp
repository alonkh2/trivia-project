#include "LoginRequestHandler.h"

#include "JsonResponsePacketSerializer.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager) :
	m_handlerFactory(handlerFactory), m_loginManager(loginManager)
{
}


/**
 * \brief Checks if a request is a login/signup request.
 * \param info The request's info.
 * \return True if the request is a login/signup request, else false.
 */
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id == LGN_CD || info.id == SU_CD;
}

/**
 * \brief Handles a request. Does nothing for now.
 * \param info The request's info.
 * \return The result of the request.
 */
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info)
{
	RequestResult rr;
	switch (info.id)
	{
	case LGN_CD:
		return login(info);
	case SU_CD:
		return signup(info);
	default:
		break;
	}
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
	LoginResponse lr;
	lr.status = 1;
	RequestResult rr;
	rr.newHandler = nullptr;
	const auto response = JsonResponseSerializer::serializeResponse(lr);

	for (int i = 0; i < response.size(); ++i)
	{
		rr.buffer[i] = response[i];
	}
	return rr;
}

/**
 * \brief Performs a signup attempt. Does nothing for now.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
	SignupResponse sr;
	sr.status = 1;
	RequestResult rr;
	rr.newHandler = nullptr;
	const auto response = JsonResponseSerializer::serializeResponse(sr);

	for (int i = 0; i < response.size(); ++i)
	{
		rr.buffer[i] = response[i];
	}
	return rr;
}
