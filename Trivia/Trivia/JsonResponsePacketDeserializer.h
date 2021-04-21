#pragma once
#include <string>
#include "constants.h"
#include "json.hpp"

typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SingupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;


class JsonResponsePacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const std::vector<Byte>& buffer);
	static SignupRequest deserializeSingupRequest(const std::vector<Byte>& buffer);

private:
	static std::string strip(const std::string& text);
};
