#include "GameManager.h"


GameManager::GameManager(IDatabase& database): m_database(database)
{
}

Game GameManager::createGame(const Room& room)
{
	auto questions = m_database.getQuestions();
	Game game(std::vector<Question>(questions.begin(), questions.end()), room.getUsers());
	m_games.push_back(game);
	return game;
}

void GameManager::deleteGame()
{
	auto i = m_games.front();
}
