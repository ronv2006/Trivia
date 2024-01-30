#pragma once
#include <string>
#include <vector>
class Question {
private:
    std::string m_question;
    std::vector<std::string> m_answers;
    int m_correctAnswer;
public:
    Question(const std::string question, const std::vector<std::string> answers, const int correctAnswer);
    std::string getQuestion() const;
    std::vector<std::string> getPossibleAnswers() const;
    int getCorrectAnswerId() const;
    


};