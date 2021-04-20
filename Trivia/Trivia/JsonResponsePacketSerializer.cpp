#include "JsonResponsePacketSerializer.h"



#include "json.hpp"
#include "json.hpp"
#include "json.hpp"
#include "json.hpp"


/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::string JsonResponseSerializer::serializeResponse(const ErrorResponse& response)
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
std::string JsonResponseSerializer::serializeResponse(const LoginResponse& response)
{
	const Byte code = LGN_CD;
	const nlohmann::json msg = {{"status", response.status}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::string JsonResponseSerializer::serializeResponse(const SignupResponse& response)
{
	const Byte code = SU_CD;
	const nlohmann::json msg = {{"status", response.status}};
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param msg The message to serialize.
 * \param code The message's code.
 * \return A byte representation of the message.
 */
::std::string JsonResponseSerializer::serialize(const nlohmann::json& msg, unsigned char code)
{
	const auto json_text = msg.dump();
	std::string response;
	auto* len = new Byte[sizeof(int)];
	*reinterpret_cast<int*>(len) = json_text.size();
	response += code;

	for (auto i = 0; i < sizeof(int); ++i)
	{
		response += len[i];
	}
	
	response += json_text;

	return response;
}
