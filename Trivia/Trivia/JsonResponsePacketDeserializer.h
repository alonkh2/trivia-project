#pragma once
#include <string>

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


class my_class
{
public:
	static LoginRequest deserializerLoginRequest(char* buffer);
	static SignupRequest deserializerSingupRequest(char* buffer);
};
