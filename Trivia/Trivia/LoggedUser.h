#pragma once
#include <string>
class LoggedUser {
private:
	std::string _username;
public:
    LoggedUser() = default;
	LoggedUser(const std::string& username);
	std::string getUsername() const ;
	friend bool operator<(const LoggedUser& user1, const LoggedUser user2) {
		return user1.getUsername() < user2.getUsername();
	}
	friend bool operator>(const LoggedUser& user1, const LoggedUser user2) {
		return user1.getUsername() > user2.getUsername();
	}
	friend bool operator==(const LoggedUser& user1, const LoggedUser user2) {
		return user1.getUsername() == user2.getUsername();
	}

};