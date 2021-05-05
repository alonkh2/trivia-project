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

typedef struct getPlayersInRoomRequest
{
	unsigned roomId;
} getPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned maxUsers;
	unsigned questionCount;
	unsigned answerTimeout;
} CreateRoomRequest;


class JsonResponsePacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const std::vector<Byte>& buffer);
	static SignupRequest deserializeSingupRequest(const std::vector<Byte>& buffer);
	static getPlayersInRoomRequest deserializeGetPlayerRequest(const std::vector<Byte>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<Byte>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<Byte>& buffer);

private:
	static std::string strip(const std::string& text);
	static nlohmann::json toJson(const std::vector<Byte>& buffer);
};
