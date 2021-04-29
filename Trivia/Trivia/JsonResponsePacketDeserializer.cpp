#include "JsonResponsePacketDeserializer.h"

#include "LoginException.h"

/**
 * \brief Deserializes a login request.
 * \param buffer The request to deserialize.
 * \return A formatted LoginRequest.
 */
LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(const std::vector<Byte>& buffer)
{
	LoginRequest lnReq;
	const auto data = std::string(buffer.begin(), buffer.end());
	const auto msg = nlohmann::json::parse(data);

	try 
	{
		lnReq.username = msg.at("username").dump();
		lnReq.password = msg.at("password").dump();

		lnReq.username = strip(lnReq.username);
		lnReq.password = strip(lnReq.password);
	}
	catch (const std::exception& e)
	{
		throw LoginException("Error deserializing LoginRequest", DSRL);
	}

	return lnReq;
}

/**
 * \brief Deserializes a signup request.
 * \param buffer The request to deserialize.
 * \return A formatted SignupRequest.
 */
SignupRequest JsonResponsePacketDeserializer::deserializeSingupRequest(const std::vector<Byte>& buffer)
{
	SignupRequest snReq;
	const auto data = std::string(buffer.begin(), buffer.end());
	const auto msg = nlohmann::json::parse(data);

	try
	{
		snReq.email = msg.at("mail").dump();
		snReq.username = msg.at("username").dump();
		snReq.password = msg.at("password").dump();

		snReq.email = strip(snReq.email);
		snReq.username = strip(snReq.username);
		snReq.password = strip(snReq.password);
	}
	catch(std::exception& e)
	{
		throw LoginException("Error deserializing LoginRequest", DSRL);
	}


	return snReq;
}

std::string JsonResponsePacketDeserializer::strip(const std::string& text)
{
	return text.substr(1, text.length() - 2);
}


