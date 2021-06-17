#pragma once
#include "Game.h"
#include "Singleton.h"
#include "IDatabase.h"
#include "Question.h"

class GameManager : public Singleton<GameManager>
{
public:
	Game& createGame(const Room& room);
	void deleteGame();

	void updateScore(const GameData& data) const;

	friend class Singleton;
private:
	GameManager(IDatabase& database);

	IDatabase& m_database;
	std::map<Room, Game> m_games;
	std::mutex m_mutex;
};
