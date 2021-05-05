#include "JsonResponsePacketDeserializer.h"

#include "CommunicationException.h"

/**
 * \brief Deserializes a login request.
 * \param buffer The request to deserialize.
 * \return A formatted LoginRequest.
 */
LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(const std::vector<Byte>& buffer)
{
	LoginRequest lnReq{};
	const auto msg = toJson(buffer);

	try 
	{
		lnReq.username = strip(msg.at("username").dump());
		lnReq.password = strip(msg.at("password").dump());
	}
	catch (...)
	{
		throw CommunicationException("Error deserializing LoginRequest", DSRL);
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
	SignupRequest snReq{};
	const auto msg = toJson(buffer);

	try
	{
		snReq.email = strip(msg.at("mail").dump());
		snReq.username = strip(msg.at("username").dump());
		snReq.password = strip(msg.at("password").dump());
	}
	catch(...)
	{
		throw CommunicationException("Error deserializing LoginRequest", DSRL);
	}


	return snReq;
}

getPlayersInRoomRequest JsonResponsePacketDeserializer::deserializeGetPlayerRequest(const std::vector<Byte>& buffer)
{
	getPlayersInRoomRequest gpirReq{};
	const auto msg = toJson(buffer);

	try
	{
		gpirReq.roomId = strtol(strip(msg.at("roomID").dump()).c_str(), nullptr, 10);
	}
	catch (...)
	{
		throw CommunicationException("Error deserializing GetPlayersInRoomRequest", DSRL);
	}
	return gpirReq;
}

JoinRoomRequest JsonResponsePacketDeserializer::deserializeJoinRoomRequest(const std::vector<Byte>& buffer)
{
	JoinRoomRequest jrReq{};
	const auto msg = toJson(buffer);

	try
	{
		jrReq.roomId = strtol(strip(msg.at("roomID").dump()).c_str(), nullptr, 10);
	}
	catch (...)
	{
		throw CommunicationException("Error deserializing JoinRoomRequest", DSRL);
	}
	return jrReq;
}

CreateRoomRequest JsonResponsePacketDeserializer::deserializeCreateRoomRequest(const std::vector<Byte>& buffer)
{
	CreateRoomRequest crReq{};

	const auto msg = toJson(buffer);
	
	try
	{
		crReq.roomName = strip(msg.at("name").dump());
		crReq.answerTimeout = strtol(strip(msg.at("timeout").dump()).c_str(), nullptr, 10);
		crReq.maxUsers = strtol(strip(msg.at("max").dump()).c_str(), nullptr, 10);
		crReq.questionCount = strtol(strip(msg.at("count").dump()).c_str(), nullptr, 10);
	}
	catch (...)
	{
		throw CommunicationException("Error deserializing CreateRoomRequest", DSRL);
	}
	return crReq;
}

std::string JsonResponsePacketDeserializer::strip(const std::string& text)
{
	return text.substr(1, text.length() - 2);
}

nlohmann::json JsonResponsePacketDeserializer::toJson(const std::vector<Byte>& buffer)
{
	return nlohmann::json::parse(std::string(buffer.begin(), buffer.end()));
}
