#pragma once

#include "IDatabase.h"
#include "Singleton.h"

// Empty class, will implement later.
class SqliteDatabase : public Singleton<SqliteDatabase, IDatabase>
{
};
