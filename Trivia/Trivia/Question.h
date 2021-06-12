#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question();
	Question(std::string question, std::vector<std::string> answers, unsigned correctAnswer);

	void setQuestion(const std::string& question);
	void addAnswer(const std::string& answer);
	void setAnswer(unsigned answer);
	
	
	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	unsigned getCorrectAnswer() const;


private:
	std::string m_question;
	std::vector<std::string> m_answers;
	unsigned m_correctAnswer;
};
