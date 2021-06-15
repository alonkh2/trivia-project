#include "Game.h"

#include <utility>

#include "CommunicationException.h"


Game::Game(std::vector<Question> questions, const std::vector<LoggedUser>& users): m_questions(std::move(questions))
{
	for (const auto& user : users)
	{
		m_players.insert(std::pair<LoggedUser, GameData>(user, GameData(user.getUsername())));
	}
}


Question Game::getQuestionForUser(const LoggedUser& user)
{
	if (m_players.find(user) != m_players.end())
	{
		return m_questions[m_players.at(user).currentQuestion];
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


unsigned Game::submitAnswer(const LoggedUser& user, unsigned answer)
{
	if (m_players.find(user) != m_players.end())
	{
		if (m_questions[m_players.at(user).currentQuestion].getCorrectAnswer() == answer)
		{
			m_players.at(user).correctAnswerCount++;
			m_players.at(user).score += 50;
		}
		else
		{
			m_players.at(user).wrongAnswerCount++;
		}
		return m_questions[m_players.at(user).currentQuestion++].getCorrectAnswer();
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


void Game::removeUser(const LoggedUser& user)
{
	if (m_players.find(user) != m_players.end())
	{
		m_players.erase(user);
		return;
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}

std::vector<GameData> Game::getResults()
{
	std::vector<GameData> results;
	for (auto player : m_players)
	{
		results.push_back(player.second);
	}
	return results;
}
