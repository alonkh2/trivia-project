#include "Question.h"

#include <utility>

Question::Question(std::string question, std::vector<std::string> answers, unsigned correctAnswer):
	m_question(std::move(question)), m_answers(std::move(answers)), m_correctAnswer(correctAnswer)
{
}


unsigned Question::getCorrectAnswer() const
{
	return m_correctAnswer;
}

std::string Question::getPossibleAnswers() const
{
	std::string answers;
	for (const auto& answer : m_answers)
	{
		answers += answer + ",";
	}
	return answers.substr(0, answers.length() - 1);
}

std::string Question::getQuestion() const
{
	return m_question;
}
