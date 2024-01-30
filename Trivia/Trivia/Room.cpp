#include "Room.h"


Room::Room(const LoggedUser & admin, const RoomData & data) : m_metadata(data), m_admin(admin)
{
    std::lock_guard<std::mutex> guard(this->m_usersMutex);
    addUser(admin);    
    
}


Room& Room::operator=(const Room& other)
{
    if (&other != this) {
        std::unique_lock<std::mutex> lock_this(this->m_usersMutex, std::defer_lock);
        std::unique_lock<std::mutex> lock_other(other.m_usersMutex, std::defer_lock);
        std::lock(lock_this, lock_other);

        this->m_metadata = other.m_metadata;
        this->m_users = other.m_users;
        this->m_admin = other.m_admin;
    }

    return *this;
}

int Room::addUser(const LoggedUser & user)
{
    if (this->m_metadata.maxPlayers != this->m_users.size()) {
        std::unique_lock<std::mutex> lock_this(this->m_usersMutex, std::defer_lock);
        this->m_users.insert(user);
        return 1;
    }
    return 0;
    
}

void Room::removeUser(const LoggedUser & user)
{
    std::lock_guard<std::mutex> guard(this->m_usersMutex);
    this->m_users.erase(user);
}

std::vector<std::string> Room::getAllUsers() 
{
    std::lock_guard<std::mutex> guard(this->m_usersMutex);
	std::vector<std::string> users;
	for (auto& it : this->m_users) {
		users.push_back(it.getUsername());
	}
	return users;
}

RoomData& Room::getRoomData()
{
    return this->m_metadata;
}
