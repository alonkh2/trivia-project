#include "LoginRequestHandler.h"

#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"

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
		rr.newHandler = nullptr;
		return rr;
	}
}

/**
 * \brief Performs a login attempt. Does nothing for now.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult LoginRequestHandler::login(const RequestInfo& info) const
{
	RequestResult rr;
	LoginResponse lr;
	rr.newHandler = nullptr;
	try
	{
		const auto data = JsonResponsePacketDeserializer::deserializeLoginRequest(info.buffer);
		m_loginManager.login(data.username, data.password);
		lr.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lr);
		// rr.newHandler = nullptr;
		rr.newHandler = m_handlerFactory.createMenuRequestHandler();
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = std::string(e.what());
		rr.newHandler = m_handlerFactory.createLoginRequestHandler();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
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
	try
	{
		const auto data = JsonResponsePacketDeserializer::deserializeSingupRequest(info.buffer);
		m_loginManager.signup(data.username, data.password, data.email);
		sr.status.push_back('1');
	}
	catch (std::exception& e)
	{
		sr.status.push_back('0');
		std::cout << e.what() << std::endl;
	}
	RequestResult rr;
	rr.newHandler = nullptr;
	rr.buffer = JsonResponsePacketSerializer::serializeResponse(sr);
	return rr;
}
