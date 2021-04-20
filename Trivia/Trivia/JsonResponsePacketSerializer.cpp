#include "JsonResponsePacketSerializer.h"

#include <iostream>



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
	std::string returnData;
	for (auto value : serialize(msg, code))
	{
		returnData += value;
	}
	return returnData;
}

/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponseSerializer::serializeResponse(const LoginResponse& response)
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
std::vector<Byte> JsonResponseSerializer::serializeResponse(const SignupResponse& response)
{
	const Byte code = SU_CD;
	const nlohmann::json msg = {{"status", response.status}};
	auto str = serialize(msg, code);
	std::cout << str.data() << std::endl;
	return str;
}

/**
 * \brief Serializes a response.
 * \param msg The message to serialize.
 * \param code The message's code.
 * \return A byte representation of the message.
 */
::std::vector<Byte> JsonResponseSerializer::serialize(const nlohmann::json& msg, unsigned char code)
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

	std::cout << response.data() << std::endl;
	return response;
}
