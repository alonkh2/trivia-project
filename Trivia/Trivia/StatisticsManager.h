﻿#pragma once

#include <vector>


#include "Singleton.h"
#include "IDatabase.h"

class StatisticsManager : public Singleton<StatisticsManager>
{
public:
	std::vector<std::string> getStatistics();
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(const std::string& username);

	friend class Singleton;
private:
	StatisticsManager(IDatabase& database);
	
	IDatabase& m_database;

	
};
