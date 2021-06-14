#include "GameManager.h"


GameManager::GameManager(IDatabase& database): m_database(database)
{
}

Game& GameManager::createGame(const Room& room)
{
	
	auto questions = m_database.getQuestions(room.getRoomData().numOfQuestions);
	if (m_games.find(room) == m_games.end())
	{
		// fix that later
		std::vector<LoggedUser> users;
		for (const auto& user : room.getUsers())
		{
			users.emplace_back(user.getUsername());
		}
		std::vector<Question> qs;
		for (const auto& question : questions)
		{
			qs.push_back(question);
		}
		auto game = Game(qs, users);
		m_games.insert(std::pair<Room, Game>(room, game));
	}
	return m_games.at(room);
}

void GameManager::deleteGame()
{
	auto i = m_games.begin();
}
