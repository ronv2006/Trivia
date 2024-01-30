#pragma once
#include <string>
#include <list>
#include "Question.h"
#include "sqlite3.h"
class IDatabase {
public:

	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExit(const std::string& username) const = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) const = 0;
	virtual bool addNewUser(const std::string& username, const std::string& password, const std::string& email) const = 0;
    virtual void addQuestionsToDatabase() const = 0;
    virtual std::list<Question> getQuestions(int) const = 0;
    virtual float getPlayersAverageAnswerTime(std::string) const = 0;
    virtual int getNumOfCorrectAnswers(std::string) const = 0;
    virtual int getNumOfTotalAnswers(std::string) const = 0;
    virtual int getNumOfPlayerGames(std::string) const = 0;
    virtual int getPlayerScore(std::string) const = 0;
    virtual std::vector<std::string> getHighScores() const = 0;
    
	virtual ~IDatabase() = default;
  




};

