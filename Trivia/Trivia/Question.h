#pragma once
#include <string>
#include <vector>
class Question;

class Question
{
public:
	Question(std::string question, std::vector<std::string> answers, unsigned correctAnswer);

	std::string getQuestion() const;
	std::string getPossibleAnswers() const;
	unsigned getCorrectAnswer() const;


private:
	std::string m_question;
	std::vector<std::string> m_answers;
	unsigned m_correctAnswer;
};
