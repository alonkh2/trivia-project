#pragma once

#include "IDatabase.h"
#include "Singleton.h"
#include "sqlite3.h"


class SqliteDatabase : public Singleton<SqliteDatabase, IDatabase>
{
public:
	// C'tor and D'tor
	SqliteDatabase();
	~SqliteDatabase();

	bool doesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	void addNewUser(const std::string& username, const std::string& password, const std::string& email) override;

	std::list<Question> getQuestions(int roomID) override;
	float getPlayerAverageAnswerTime(const std::string& username) override;
	int getNumOfCorrectAnswers(const std::string& username) override;
	int getNumOfTotalAnswers(const std::string& username) override;
	int getNumOfPlayerGames(const std::string& username) override;
	
private:
	sqlite3* _db;

	static int stringCallback(void* used, int argc, char** argv, char** az_col_name);
	static int statisticCallback(void* used, int argc, char** argv, char** az_col_name);
	static int questionCallback(void* used, int argc, char** argv, char** az_col_name);

	Statistic getStats(const std::string& username) const;
	template <class T>
	bool execCommand(const std::string& command, int (*foo)(void*, int, char**, char**), T* ansRef) const;
	friend class Singleton;
};
