#pragma once

#include <vector>


#include "Singleton.h"
#include "IDatabase.h"

class StatisticsManager : public Singleton<StatisticsManager>
{
public:
	std::vector<std::string> getStatistics(const std::string& username) const;
	std::vector<std::string> getHighScore() const;

	friend class Singleton;
private:
	StatisticsManager(IDatabase& database);
	
	IDatabase& m_database;
};
