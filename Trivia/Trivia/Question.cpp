#include "Question.h"

Question::Question(const std::string question, const std::vector<std::string> answers, const int correctAnswer)
{
    this->m_answers = answers;
    this->m_correctAnswer = correctAnswer;
    this->m_question = question;
}

std::string Question::getQuestion() const
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return m_answers;
}

int Question::getCorrectAnswerId() const
{
    return m_correctAnswer;
}
