#include "GameManager.h"


GameManager::GameManager(IDatabase& database): m_database(database)
{
}

/**
 * \brief Creates a game.
 * \param room The room the game is based upon.
 * \return A game.
 */
Game& GameManager::createGame(const Room& room)
{
	std::lock_guard<std::mutex> mx(m_mutex);
	if (m_games.find(room) == m_games.end())
	{
		std::vector<LoggedUser> users;
		for (const auto& user : room.getUsers())
		{
			users.emplace_back(user.getUsername());
		}
		std::vector<Question> qs;
		auto game = Game(m_database.getQuestions(room.getRoomData().numOfQuestions), users);
		m_games.insert(std::pair<Room, Game>(room, game));
	}
	return m_games.at(room);
}

/**
 * \brief Deletes all games that are empty.
 */
void GameManager::deleteGame()
{
	for (const auto& game : m_games)
	{
		if (game.second.getPlayers().empty())
		{
			m_games.erase(game.first);
		}
	}
}

/**
 * \brief Updates a player's score.
 * \param data The player's stats.
 */
void GameManager::updateScore(const GameData& data) const
{
	m_database.updateStats(data);
}
