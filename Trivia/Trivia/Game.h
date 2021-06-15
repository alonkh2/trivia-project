#pragma once
#include <map>
#include <utility>

#include "Question.h"
#include "LoggedUser.h"
#include "Room.h"

typedef struct GameData
{
	std::string username;
	unsigned currentQuestion;
	unsigned correctAnswerCount;
	unsigned wrongAnswerCount;
	float averageAnswerTime;
	unsigned score;

	GameData(std::string name): username(std::move(name)), currentQuestion(0), correctAnswerCount(0), wrongAnswerCount(0), averageAnswerTime(0), score(0) {}

	std::string toString() const
	{
		return username + "," + std::to_string(correctAnswerCount) + "," + std::to_string(wrongAnswerCount) + "," +
			std::to_string(averageAnswerTime) + "," + std::to_string(score);
	}
} GameData;

class Game
{
public:
	Game(std::vector<Question> questions, const std::vector<LoggedUser>& users);

	Question getQuestionForUser(const LoggedUser& user);
	unsigned submitAnswer(const LoggedUser& user, unsigned answer);
	void removeUser(const LoggedUser& user);

	std::vector<GameData> getResults();
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};
