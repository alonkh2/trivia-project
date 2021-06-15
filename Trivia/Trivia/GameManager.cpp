#include "GameManager.h"


GameManager::GameManager(IDatabase& database): m_database(database)
{
}

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

void GameManager::deleteGame()
{
	auto i = m_games.begin();
}
