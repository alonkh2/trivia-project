#include "Game.h"

#include <utility>

#include "CommunicationException.h"


Game::Game(std::vector<Question> questions, const std::vector<LoggedUser>& users): m_questions(std::move(questions))
{
	for (const auto& user : users)
	{
		m_players[LoggedUser(user.getUsername())] = GameData(user.getUsername());
		m_users[user.getUsername()] = GameData(user.getUsername());
	}
}


Question Game::getQuestionForUser(const LoggedUser& user)
{
	if (m_users[user.getUsername()].currentQuestion >= m_questions.size())
	{
		throw CommunicationException("Not enough questions!", NEQ);
	}
	if (m_users.find(user.getUsername()) != m_users.end())
	{
		return m_questions[m_users[user.getUsername()].currentQuestion];
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


unsigned Game::submitAnswer(const LoggedUser& user, unsigned answer)
{
	if (m_users.find(user.getUsername()) != m_users.end())
	{
		if (m_questions[m_users.at(user.getUsername()).currentQuestion].getCorrectAnswer() == answer)
		{
			m_users.at(user.getUsername()).correctAnswerCount++;
			m_users.at(user.getUsername()).score += 50;
		}
		else
		{
			m_users.at(user.getUsername()).wrongAnswerCount++;
		}
		return m_questions[m_users.at(user.getUsername()).currentQuestion++].getCorrectAnswer();
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


void Game::removeUser(const LoggedUser& user)
{
	if (m_users.find(user.getUsername()) != m_users.end())
	{
		m_users.erase(user.getUsername());
		return;
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}

std::vector<GameData> Game::getResults()
{
	std::vector<GameData> results;
	for (const auto& player : m_users)
	{
		results.push_back(player.second);
	}
	return results;
}
