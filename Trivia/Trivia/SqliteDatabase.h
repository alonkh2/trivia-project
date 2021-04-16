#pragma once

#include "IDatabase.h"
#include "Singleton.h"

class SqliteDatabase : public Singleton<SqliteDatabase, IDatabase>
{
};
