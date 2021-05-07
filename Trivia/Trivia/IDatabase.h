#pragma once
#include <list>
#include <string>


typedef struct Question
{
	std::string question;
	std::vector<std::string> options;
	unsigned correct;
} Question;


class IDatabase
{
public:
	
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;

	virtual std::list<Question> getQuestions(int roomID) = 0;
	virtual float getPlayerAverageAnswerTime() = 0;
	virtual int getNumOfCorrectAnswers() = 0;
	virtual int getNumOfTotalAnswers() = 0;
	virtual int getNumOfPlayerGames() = 0;
};
