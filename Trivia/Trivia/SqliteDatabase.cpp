#include "SqliteDatabase.h"
#include <iostream>

#include "CommunicationException.h"

/*
* This function returns the ID parameter of all tables
*/
int SqliteDatabase::stringCallback(void* used, int argc, char** argv, char** az_col_name)
{
	auto* val = static_cast<std::string*>(used);
	if (argc > 0)
	{
		*val = argv[0];
	}

	return 0;
}

/*
 * This function returns a statistic from the database.
 */
int SqliteDatabase::statisticCallback(void* used, int argc, char** argv, char** az_col_name)
{
	auto* val = static_cast<Statistic*>(used);
	if (argc > 0)
	{
		for (int i = 0; i < argc; ++i)
		{
			if (!strcmp(az_col_name[i], "average"))
			{
				val->averageTime = std::stof(std::string(argv[i]));
			}
			else if (!strcmp(az_col_name[i], "correct"))
			{
				val->correctAnswers = std::stoi(std::string(argv[i]));
			}
			else if (!strcmp(az_col_name[i], "total"))
			{
				val->totalAnswers = std::stoi(std::string(argv[i]));
			}
			else if (!strcmp(az_col_name[i], "games"))
			{
				val->playerGames = std::stoi(std::string(argv[i]));
			}
			else if (!strcmp(az_col_name[i], "score"))
			{
				val->score = std::stoi(std::string(argv[i]));
			}
		}
	}
	return 0;
}

/*
 * This function returns a question from the database.
 */
int SqliteDatabase::questionCallback(void* used, int argc, char** argv, char** az_col_name)
{
	auto* val = static_cast<std::list<Question>*>(used);
	Question q;
	if (argc > 0)
	{
		for (int i = 0; i < argc; ++i)
		{
			if (!strcmp(az_col_name[i], "question"))
			{
				q.question = std::string(argv[i]);
			}
			else if (!strcmp(az_col_name[i], "correct"))
			{
				q.correct = std::stoi(std::string(argv[i]));
			}
			else if (std::string(az_col_name[i]).substr(0, 3) == "ans")
			{
				q.options.emplace_back(argv[i]);
			}
		}
	}
	val->push_back(q);
	return 0;
}

/*
 * This function returns the top 5 scores. 
 */
int SqliteDatabase::stringVectorCallback(void* used, int argc, char** argv, char** az_col_name)
{
	auto* val = static_cast<std::vector<std::string>*>(used);
	if (argc > 0)
	{
		for (auto i = 0; i < argc; ++i)
		{
			if (!strcmp(az_col_name[i], "score") || !strcmp(az_col_name[i], "username"))
			{
				val->push_back(std::string(argv[i]) + ",");
			}	
		}
	}
	return 0;
}

/**
 * \brief Gets the statistics of a user.
 * \param username The user's name.
 * \return The user's stats.
 */
Statistic SqliteDatabase::getStats(const std::string& username) 
{
	const auto query = "SELECT * FROM STATISTICS WHERE username = '" + username + "';";
	Statistic stat;
	execCommand(query, statisticCallback, &stat);
	return stat;
}

/**
 * \brief Gets the top 5 scores.
 * \return The high scores.
 */
std::vector<std::string> SqliteDatabase::getHighScore()
{
	const std::string query = "SELECT username, score FROM statistics ORDER BY score DESC LIMIT 5";
	std::vector<std::string> scores;
	execCommand(query, stringVectorCallback, &scores);
	return scores;
}

/*
 * Please don't ask me what this does.
 */
template <class T>
bool SqliteDatabase::execCommand(const std::string& command, int (*foo)(void*, int, char**, char**),
                                 T* ansRef) const
{
	char* err;
	const int res = sqlite3_exec(_db, command.c_str(), foo, ansRef, &err);

	return res == SQLITE_OK;
}

/**
 * \brief Function constructs an SqliteDatabase
 */
SqliteDatabase::SqliteDatabase(): _db(nullptr)
{
	const std::string dbName = "triviaDB.sqlite";
	sqlite3_open(dbName.c_str(), &_db);
	std::string createTableQuery =
		"CREATE TABLE IF NOT EXISTS USERS (username TEXT PRIMARY KEY, password TEXT, email TEXT);";
	execCommand<int>(createTableQuery, nullptr, nullptr);
	createTableQuery =
		"CREATE TABLE IF NOT EXISTS QUESTIONS (question TEXT PRIMARY KEY, ans1 TEXT, ans2 TEXT, ans3 TEXT, ans4 TEXT, correct INTEGER, room_id INTEGER);";
	execCommand<int>(createTableQuery, nullptr, nullptr);
	createTableQuery =
		"CREATE TABLE IF NOT EXISTS STATISTICS (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, average REAL DEFAULT 0, correct INTEGER DEFAULT 0, total INTEGER DEFAULT 0, games INTEGER DEFAULT 0, score INTEGER DEFAULT 0, FOREIGN KEY(username) REFERENCES USERS(username));";
	execCommand<int>(createTableQuery, nullptr, nullptr);
}

/**
 * \brief Function closes the database
 */
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
}

/**
 * \brief Checks if a user exists in the database
 * \param username The user's username.
 * \return A bool indicating if a user exists in the DB.
 */
bool SqliteDatabase::doesUserExist(const std::string& username)
{
	auto sqlQuery = "SELECT username FROM USERS WHERE username = '" + username + "';";
	std::string dbResp;

	execCommand(sqlQuery, stringCallback, &dbResp);

	return dbResp == username;
}

/**
 * \brief Checks if the inputted password matches the DB
 * \param username The user's username.
 * \param password The user's password.
 * \return A bool indicating if the passwords match.
 */
bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string dbResp;
	auto passwordQuery = "SELECT password FROM USERS WHERE username = '" + username + "';";

	if (!doesUserExist(username))
	{
		auto errMsg = "User: " + username + " does not exist!";
		throw CommunicationException(std::string("User: " + username + " does not exist!"), DSNT_EXST);
	}
	execCommand(passwordQuery, stringCallback, &dbResp);

	return dbResp == password;
}

/**
 * \brief Logs a user with a given username to the server.
 * \param username The user's username.
 * \param password The user's password.
 * \param email The user's email.
 */
void SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	auto addUserQuery = "INSERT INTO USERS (username, password, email) VALUES ('" + username + "', '" + password +
		"', '" + email + "');";

	if (doesUserExist(username))
	{
		throw CommunicationException(std::string("User: " + username + " already exists!"), EXSTS);
	}

	execCommand<int>(addUserQuery, nullptr, nullptr);

	addUserQuery = "INSERT INTO statistics (username) VALUES ('" + username + "');";

	execCommand<int>(addUserQuery, nullptr, nullptr);
}

/**
 * \brief Gets a user's correct answer count.
 * \param username The user's name.
 * \return The user's correct answer count.
 */
int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username)
{
	return getStats(username).correctAnswers;
}

/**
 * \brief Gets a user's game count.
 * \param username The user's name.
 * \return The user's game count.
 */
int SqliteDatabase::getNumOfPlayerGames(const std::string& username)
{
	return getStats(username).playerGames;
}

/**
 * \brief Gets a user's total answer count.
 * \param username The user's name.
 * \return The user's total answer count.
 */
int SqliteDatabase::getNumOfTotalAnswers(const std::string& username)
{
	return getStats(username).totalAnswers;
}

/**
 * \brief Gets a user's average answer time.
 * \param username The user's name.
 * \return The user's average answer time.
 */
float SqliteDatabase::getPlayerAverageAnswerTime(const std::string& username)
{
	return getStats(username).averageTime;
}

/*
 * I do not know.
 */
std::list<Question> SqliteDatabase::getQuestions(int roomID)
{
	const auto query = "SELECT * FROM questions WHERE room_id = " + std::to_string(roomID) + ";";
	auto questions = std::list<Question>();
	execCommand(query, questionCallback, &questions);
	return questions;
}
