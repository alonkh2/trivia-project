#include "StatisticsManager.h"

#include "Server.h"


StatisticsManager::StatisticsManager(IDatabase& database) : m_database(database)
{
}

/**
 * \brief Gets a user's statistics.
 * \param username The user's name.
 * \return The user's statistics.
 */
std::vector<std::string> StatisticsManager::getStatistics(const std::string& username) const
{
	const auto stat = m_database.getStats(username);
	std::vector<std::string> stats;
	stats.push_back(std::to_string(stat.totalAnswers));
	stats.push_back(std::to_string(stat.correctAnswers));
	stats.push_back(std::to_string(stat.playerGames));
	stats.push_back(std::to_string(stat.averageTime));
	stats.push_back(std::to_string(stat.score));
	return stats;
}

/**
 * \brief Gets the top 5 scores.
 * \return The high scores.
 */
std::vector<std::string> StatisticsManager::getHighScore() const
{
	auto val = m_database.getHighScore();
	return val;
}
