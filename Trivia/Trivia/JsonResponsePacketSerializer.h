#pragma once
#include <string>
#include "vector"

#include "constants.h"
#include "json.hpp"
#include "Room.h"


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

typedef struct LogoutResponse
{
	unsigned status;
} LogoutResponse;


typedef struct GetRoomsResponse
{
	unsigned status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse
{
	unsigned status;
	std::vector<std::string> statistics;
} GetHighScoreResponse;

typedef struct GetPersonalStatsResponse
{
	unsigned status;
	std::vector<std::string> statistics;
} GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	unsigned status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned status;
} CreateRoomResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<Byte> serializeResponse(const ErrorResponse& response);
	static std::vector<Byte> serializeResponse(const LoginResponse& response);
	static std::vector<Byte> serializeResponse(const SignupResponse& response);

private:
	static std::vector<Byte> serialize(const nlohmann::json& msg, Byte code);
};
