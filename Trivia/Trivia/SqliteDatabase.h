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

private:
	sqlite3* _db;

	bool execCommand(const std::string& command, int (*foo)(void*, int, char**, char**), std::string* ansRef) const;
	friend class Singleton;
};
