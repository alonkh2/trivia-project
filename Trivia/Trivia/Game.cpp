﻿#include "Game.h"

#include <utility>

#include "CommunicationException.h"


Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& users)
{
	for (const auto& user : users)
	{
		m_players.insert_or_assign(user, GameData{});
	}
}


std::string Game::getQuestionForUser(const LoggedUser& user)
{
	if (m_players.find(user) != m_players.end())
	{
		return m_questions[m_players.at(user).currentQuestion].getQuestion();
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
		}
		else
		{
			m_players.at(user).wrongAnswerCount++;
		}
		m_players.at(user).currentQuestion++;
		return m_questions[m_players.at(user).currentQuestion].getCorrectAnswer();
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


void Game::removeUser(const LoggedUser& user)
{
	if (m_players.find(user) != m_players.end())
	{
		m_players.erase(user);
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}
