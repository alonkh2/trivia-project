#include "Question.h"

#include <utility>

Question::Question(): m_question(""), m_correctAnswer(0)
{
}

Question::Question(std::string question, std::vector<std::string> answers, unsigned correctAnswer):
	m_question(std::move(question)), m_answers(std::move(answers)), m_correctAnswer(correctAnswer)
{
}

/**
 * \brief m_question setter.
 * \param question The new question.
 */
void Question::setQuestion(const std::string& question)
{
	m_question = question;
}


/**
 * \brief Adds an answer.
 * \param answer An answer.
 */
void Question::addAnswer(const std::string& answer)
{
	m_answers.push_back(answer);
}

/**
 * \brief Sets the correct answer.
 * \param answer The correct answers.
 */
void Question::setAnswer(unsigned answer)
{
	m_correctAnswer = answer;
}

/**
 * \brief m_correctAnswer getter.
 * \return The correct answer.
 */
unsigned Question::getCorrectAnswer() const
{
	return m_correctAnswer;
}

/**
 * \brief m_answers getter.
 * \return The possible answers.
 */
std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_answers;
}

/**
 * \brief m_question getter.
 * \return The question.
 */
std::string Question::getQuestion() const
{
	return m_question;
}
