#pragma once
#include <list>
#include <string>
#include <vector>

#include "Question.h"


typedef struct Statistic
{
	float averageTime;
	int correctAnswers;
	int totalAnswers;
	int playerGames;
	int score;
} Statistic;


class IDatabase
{
public:
	// Login functions
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;

	// Questions and statistics
	virtual std::list<Question> getQuestions() = 0;
	virtual float getPlayerAverageAnswerTime(const std::string& username) = 0;
	virtual int getNumOfCorrectAnswers(const std::string& username) = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) = 0;
	virtual int getNumOfPlayerGames(const std::string& username) = 0;

	virtual Statistic getStats(const std::string& username) = 0;
	virtual std::vector<std::string> getHighScore() = 0;
};
