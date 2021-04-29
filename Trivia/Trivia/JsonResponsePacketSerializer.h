#pragma once
#include <string>
#include "vector"

#include "constants.h"
#include "json.hpp"




typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LoginResponse
{
	std::vector<Byte> status;
} LoginResponse;

typedef struct SignupResponse
{
	std::vector<Byte> status;
} SignupResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<Byte> serializeResponse(const ErrorResponse& response);
	static std::vector<Byte> serializeResponse(const LoginResponse& response);
	static std::vector<Byte> serializeResponse(const SignupResponse& response);

private:
	static std::vector<Byte> serialize(const nlohmann::json& msg, Byte code);
};
