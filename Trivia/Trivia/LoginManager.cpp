#include "LoginManager.h"

LoginManager::LoginManager(std::weak_ptr<IDatabase>& db)
{
    this->m_database = db;
}

bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	auto database = this->m_database.lock();
	if (database->addNewUser(username, password, email)) {
		login(username, password);
		return true;
	}
	
	return false;
}

bool LoginManager::login(const std::string& username, const std::string& password)
{
    auto database = this->m_database.lock();
    std::lock_guard<std::mutex> guard(this->m_loggedUsersMutex);
    for (auto& it : this->m_loggedUsers) {
        if (it.getUsername() == username) {
            return false;
        }
    }
    if (!database.get()->doesPasswordMatch(username, password)) {
        return false;
    }

    this->m_loggedUsers.push_back(LoggedUser(username));
    return true;
}

void LoginManager::logout(std::string& username)
{
    std::lock_guard<std::mutex> guard(this->m_loggedUsersMutex);
    this->m_loggedUsers.erase(std::remove_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), [username](LoggedUser lu) {return lu.getUsername() == username; }));



}
