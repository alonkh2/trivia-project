#include "Question.h"

#include <utility>

Question::Question(): m_question(""), m_correctAnswer(0)
{
}

Question::Question(std::string question, std::vector<std::string> answers, unsigned correctAnswer):
	m_question(std::move(question)), m_answers(std::move(answers)), m_correctAnswer(correctAnswer)
{
}

void Question::setQuestion(const std::string& question)
{
	m_question = question;
}


void Question::addAnswer(const std::string& answer)
{
	m_answers.push_back(answer);
}

void Question::setAnswer(unsigned answer)
{
	m_correctAnswer = answer;
}

unsigned Question::getCorrectAnswer() const
{
	return m_correctAnswer;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_answers;
}

std::string Question::getQuestion() const
{
	return m_question;
}
