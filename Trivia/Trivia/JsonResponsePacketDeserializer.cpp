#include "JsonResponsePacketDeserializer.h"

/**
 * \brief Deserializes a login request.
 * \param buffer The request to deserialize.
 * \return A formatted LoginRequest.
 */
LoginRequest JsonPacketDeserializer::deserializeLoginRequest(char* buffer)
{
	LoginRequest lnReq;
	const nlohmann::json msg = nlohmann::json::parse(buffer);

	try 
	{
		lnReq.username = msg.at("username").dump();
		lnReq.password = msg.at("password").dump();
	}
	
	catch (const std::exception& e)
	{
		throw std::exception("Error deserializing LoginRequest");
	}

	return lnReq;
}

/**
 * \brief Deserializes a signup request.
 * \param buffer The request to deserialize.
 * \return A formatted SignupRequest.
 */
SignupRequest JsonPacketDeserializer::deserializeSingupRequest(char* buffer)
{
	SignupRequest snReq;
	const nlohmann::json msg = nlohmann::json::parse(buffer);

	try
	{
		snReq.email = msg.at("email").dump();
		snReq.username = msg.at("username").dump();
		snReq.password = msg.at("password").dump();

	}

	catch(std::exception& e)
	{
		throw std::exception("Error deserializing LoginRequest");
	}


	return snReq;
}


