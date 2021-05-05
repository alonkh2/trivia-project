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
	std::vector<Byte> status;
} LogoutResponse;


typedef struct GetRoomsResponse
{
	std::vector<Byte> status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse
{
	std::vector<Byte> status;
	std::vector<std::string> statistics;
} GetHighScoreResponse;

typedef struct GetPersonalStatsResponse
{
	std::vector<Byte> status;
	std::vector<std::string> statistics;
} GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	std::vector<Byte> status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	std::vector<Byte> status;
} CreateRoomResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<Byte> serializeResponse(const ErrorResponse& response);
	static std::vector<Byte> serializeResponse(const LoginResponse& response);
	static std::vector<Byte> serializeResponse(const SignupResponse& response);
	static std::vector<Byte> serializeResponse(const LogoutResponse& response);
	static std::vector<Byte> serializeResponse(const GetRoomsResponse& response);
	static std::vector<Byte> serializeResponse(const JoinRoomResponse& response);
	static std::vector<Byte> serializeResponse(const CreateRoomResponse& response);
	static std::vector<Byte> serializeResponse(const GetPersonalStatsResponse& response);

private:
	static std::vector<Byte> serialize(const nlohmann::json& msg, Byte code);
};
