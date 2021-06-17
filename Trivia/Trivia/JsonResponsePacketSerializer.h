#pragma once
#include <string>
#include "vector"

#include "constants.h"
#include "Game.h"
#include "json.hpp"
#include "Room.h"


typedef struct PlayerResults
{
	std::string username;
	unsigned correctAnswerCount;
	unsigned wrongAnswerCount;
	float averageAnswerTime;

	std::string toString() const
	{
		return username + "," + std::to_string(correctAnswerCount) + "," + std::to_string(wrongAnswerCount) + "," +
			std::to_string(averageAnswerTime);
	}
} PlayerResults;

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
	unsigned id;
} CreateRoomResponse;

typedef struct CloseRoomResponse
{
	std::vector<Byte> status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	std::vector<Byte> status;
} StartGameResponse;

typedef struct GetRoomStateResponse
{
	std::vector<Byte> status;
	int state;
	std::vector<std::string> players;
	unsigned questionCount;
	float answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	std::vector<Byte> status;
} LeaveRoomResponse;


typedef struct LeaveGameResponse
{
	std::vector<Byte> status;
} LeaveGameResponse;

typedef struct GetQuestionResponse
{
	std::vector<Byte> status;
	std::string question;
	std::map<unsigned, std::string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	std::vector<Byte> status;
	unsigned correctAnswer;
} SubmitAnswerResponse;

typedef struct GetGameResultsResponse
{
	std::vector<Byte> status;
	std::vector<GameData> results;
} GetGameResultsResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<Byte> serializeResponse(const ErrorResponse& response);
	static std::vector<Byte> serializeResponse(const LoginResponse& response);
	static std::vector<Byte> serializeResponse(const SignupResponse& response);
	static std::vector<Byte> serializeResponse(const LogoutResponse& response);
	static std::vector<Byte> serializeResponse(const GetRoomsResponse& response);
	static std::vector<Byte> serializeResponse(const GetPlayersInRoomResponse& response);
	static std::vector<Byte> serializeResponse(const GetHighScoreResponse& response);
	static std::vector<Byte> serializeResponse(const JoinRoomResponse& response);
	static std::vector<Byte> serializeResponse(const CreateRoomResponse& response);
	static std::vector<Byte> serializeResponse(const GetPersonalStatsResponse& response);
	static std::vector<Byte> serializeResponse(const CloseRoomResponse& response);
	static std::vector<Byte> serializeResponse(const StartGameResponse& response);
	static std::vector<Byte> serializeResponse(const GetRoomStateResponse& response);
	static std::vector<Byte> serializeResponse(const LeaveRoomResponse& response);
	static std::vector<Byte> serializeResponse(const LeaveGameResponse& response);
	static std::vector<Byte> serializeResponse(const GetQuestionResponse& response);
	static std::vector<Byte> serializeResponse(const SubmitAnswerResponse& response);
	static std::vector<Byte> serializeResponse(const GetGameResultsResponse& response);

private:
	static std::vector<Byte> serialize(const nlohmann::json& msg, Byte code);
};
