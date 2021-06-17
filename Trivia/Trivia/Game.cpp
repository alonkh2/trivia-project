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


/**
 * \brief Gets a question for a user.
 * \param user The user.
 * \return The user's next question.
 */
Question Game::getQuestionForUser(const LoggedUser& user)
{
	if (m_users[user.getUsername()].currentQuestion >= m_questions.size())
	{
		throw CommunicationException("Not enough questions!", NEQ);
	}
	if (m_users.find(user.getUsername()) != m_users.end())
	{
		m_users[user.getUsername()].time = time(nullptr);
		return m_questions[m_users[user.getUsername()].currentQuestion];
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


/**
 * \brief Submits a user's answer.
 * \param user The user.
 * \param answer The user's answer.
 * \return The correct answer.
 */
unsigned Game::submitAnswer(const LoggedUser& user, unsigned answer)
{
	if (m_users.find(user.getUsername()) != m_users.end())
	{
		if (m_questions[m_users.at(user.getUsername()).currentQuestion].getCorrectAnswer() == answer)
		{
			m_users.at(user.getUsername()).correctAnswerCount++;
		}
		else
		{
			m_users.at(user.getUsername()).wrongAnswerCount++;
		}
		auto time_ = time(nullptr) - m_users.at(user.getUsername()).time;
		if (time_ < 0)
		{
			time_ = 0;
		}
		m_users.at(user.getUsername()).totalTime += time_;
		m_users.at(user.getUsername()).averageAnswerTime = m_users.at(user.getUsername()).totalTime / (static_cast<long long>(m_users.at(user.getUsername()).currentQuestion) + static_cast<float>(1));
		if (m_users.at(user.getUsername()).currentQuestion == m_questions.size() - 1)
		{
			calculateScore(user);
		}
		return m_questions[m_users.at(user.getUsername()).currentQuestion++].getCorrectAnswer();
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}


/**
 * \brief Removes a user from the game.
 * \param user The user to remove.
 * \return The user's stats.
 */
GameData Game::removeUser(const LoggedUser& user)
{
	if (m_users.find(user.getUsername()) != m_users.end())
	{
		calculateScore(user);
		auto data = m_users.at(user.getUsername());
		m_users.erase(user.getUsername());
		return data;
	}
	throw CommunicationException("Player doesn't exist in room!", DSNT_EXST);
}

/**
 * \brief m_players getter.
 * \return The players.
 */
std::map<LoggedUser, GameData> Game::getPlayers() const
{
	return m_players;
}

/**
 * \brief results getter.
 * \return The results.
 */
std::vector<GameData> Game::getResults()
{
	std::vector<GameData> results;
	for (const auto& player : m_users)
	{
		results.push_back(player.second);
	}
	return results;
}

/**
 * \brief Calculates a user's score.
 * \param user The user.
 */
void Game::calculateScore(const LoggedUser& user)
{
	// 20 points for each correct answer, 5 points * (10 - average time). Minimal score is zero.
	int score = m_users[user.getUsername()].correctAnswerCount * 20;
	score += (10 - m_users[user.getUsername()].averageAnswerTime) * 5 * (m_users[user.getUsername()].correctAnswerCount > 0);
	if (score > 0)
		m_users[user.getUsername()].score = score;
	else
		m_users[user.getUsername()].score = 0;
}
