#pragma once
#include <string>

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned status;
} SignupResponse;

class JsonResponseSerializer
{
public:
	static char* serializeResponse(const ErrorResponse& response);
	static char* serializeResponse(const LoginResponse& response);
	static char* serializeResponse(const SignupResponse& response);
};
