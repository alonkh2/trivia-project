#pragma once
#include <map>
#include <utility>

#include "Question.h"
#include "LoggedUser.h"
#include "Room.h"

typedef struct GameData
{
	unsigned currentQuestion;
	unsigned correctAnswerCount;
	unsigned wrongAnswerCount;
	float averageAnswerTime;

	GameData(): currentQuestion(0), correctAnswerCount(0), wrongAnswerCount(0), averageAnswerTime(0) {}
} GameData;

class Game
{
public:
	Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& users);

	std::string getQuestionForUser(const LoggedUser& user);
	unsigned submitAnswer(const LoggedUser& user, unsigned answer);
	void removeUser(const LoggedUser& user);

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};
