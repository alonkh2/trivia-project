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
