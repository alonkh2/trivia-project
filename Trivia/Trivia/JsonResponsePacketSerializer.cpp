#include "JsonResponsePacketSerializer.h"


/**
 * \brief Serializes a response.
 * \param response The response to be sent.
 * \return A byte representation of the message.
 */
std::vector<Byte> JsonResponseSerializer::serializeResponse(const ErrorResponse& response)
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
	return serialize(msg, code);
}

/**
 * \brief Serializes a response.
 * \param msg The message to serialize.
 * \param code The message's code.
 * \return A byte representation of the message.
 */
std::vector<unsigned char> JsonResponseSerializer::serialize(const nlohmann::json& msg, unsigned char code)
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

	std::vector<Byte> resp;
	for (auto value : response)
	{
		resp.push_back(value);
	}
	return resp;
}
