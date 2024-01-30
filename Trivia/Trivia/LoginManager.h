#pragma once
#include <memory>
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
#include <mutex>
class LoginManager {
public:
    LoginManager(std::weak_ptr<IDatabase>& db);
    bool signup(const std::string& username, const std::string& password, const std::string& email);
    bool login(const std::string& username, const std::string& password);
    void logout(std::string& username);
private:
    std::vector<LoggedUser> m_loggedUsers;
    std::mutex m_loggedUsersMutex;
    std::weak_ptr<IDatabase> m_database;
};
