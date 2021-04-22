#pragma once

#include "IDatabase.h"
#include "Singleton.h"
#include "sqlite3.h"

class SqliteDatabase : public Singleton<SqliteDatabase, IDatabase>
{
public:

	SqliteDatabase();
	~SqliteDatabase();

	bool doesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	void addNewUser(const std::string& username, const std::string& password, const std::string& email) override;

private:
	bool execCommand(const std::string command, int (*foo)(void*, int, char**, char**), std::string* ansRef);
	sqlite3* _db;

	friend class Singleton;
};
