#include "JsonResponsePacketDeserializer.h"

/**
 * \brief Deserializes a login request.
 * \param buffer The request to deserialize.
 * \return A formatted LoginRequest.
 */
LoginRequest JsonPacketDeserializer::deserializeLoginRequest(const std::vector<Byte>& buffer)
{
	LoginRequest lnReq;
	std::string strBuffer;
	for (auto value : buffer)
	{
		strBuffer += value;
	}
	const nlohmann::json msg = nlohmann::json::parse(strBuffer);

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
SignupRequest JsonPacketDeserializer::deserializeSingupRequest(const std::vector<Byte>& buffer)
{
	SignupRequest snReq;
	std::string strBuffer;
	for (auto value : buffer)
	{
		strBuffer += value;
	}
	const nlohmann::json msg = nlohmann::json::parse(strBuffer);

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


