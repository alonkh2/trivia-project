#include "JsonResponsePacketSerializer.h"

#include <iostream>


#include "json.hpp"

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
	const Byte code = ERR_CD;
	const nlohmann::json msg = {{"message", response.message}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
	const Byte code = LGN_CD;
	const nlohmann::json msg = {{"status", std::string(response.status.begin(), response.status.end())}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
	const Byte code = SU_CD;
	const nlohmann::json msg = {{"status", std::string(response.status.begin(), response.status.end())}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
	const Byte code = SO_CD;
	const nlohmann::json msg = {{"status", std::string(response.status.begin(), response.status.end())}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
	const Byte code = GR_CD;
	std::vector<std::string> data;
	for (const auto& room : response.rooms)
	{
		data.push_back(room.toString() + "$");
	}
	const nlohmann::json msg = {
		{"status", std::string(response.status.begin(), response.status.end())},
		{"rooms", std::accumulate(data.begin(), data.end(), std::string{})}
	};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
	const Byte code = GPR_CD;
	const nlohmann::json msg = {
		{"players", std::accumulate(response.players.begin(), response.players.end(), std::string{})}
	};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
	const Byte code = GHS_CD;
	const nlohmann::json msg = {
		{"status", std::string(response.status.begin(), response.status.end())},
		{"statistics", std::accumulate(response.statistics.begin(), response.statistics.end(), std::string{})}
	};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
	const Byte code = JR_CD;
	const nlohmann::json msg = {{"status", std::string(response.status.begin(), response.status.end())}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
	const Byte code = CR_CD;
	const nlohmann::json msg = {{"status", std::string(response.status.begin(), response.status.end())}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
	const Byte code = GPS_CD;
	const nlohmann::json msg = {
		{"status", std::string(response.status.begin(), response.status.end())},
		{"statistics", std::accumulate(response.statistics.begin(), response.statistics.end(), std::string{})}
	};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param msg The message to serialize.
 * \param code The message's code.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponsePacketSerializer::serialize(const nlohmann::json& msg, unsigned char code)
{
	const auto json_text = msg.dump();
	std::vector<Byte> response;
	auto* len = new Byte[sizeof(int)];
	*reinterpret_cast<int*>(len) = json_text.size();
	response.push_back(code);

	for (auto i = 0; i < sizeof(int); ++i)
	{
		response.push_back(len[i]);
	}

	for (auto text : json_text)
	{
		response.push_back(text);
	}
	return response;
}
