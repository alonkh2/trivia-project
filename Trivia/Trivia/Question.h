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


	friend bool operator<(const Question& lhs, const Question& rhs)
	{
		if (lhs.m_question < rhs.m_question)
			return true;
		if (rhs.m_question < lhs.m_question)
			return false;
		if (lhs.m_answers < rhs.m_answers)
			return true;
		if (rhs.m_answers < lhs.m_answers)
			return false;
		return lhs.m_correctAnswer < rhs.m_correctAnswer;
	}

	friend bool operator<=(const Question& lhs, const Question& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const Question& lhs, const Question& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const Question& lhs, const Question& rhs)
	{
		return !(lhs < rhs);
	}

private:
	std::string m_question;
	std::vector<std::string> m_answers;
	unsigned m_correctAnswer;
};
