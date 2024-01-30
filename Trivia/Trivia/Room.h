#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>
#include <set>
#include <mutex>
class Room {
private:
	RoomData m_metadata;
	std::set<LoggedUser> m_users;
    LoggedUser m_admin;
    mutable std::mutex m_usersMutex;
    
public:
    Room() = default;
    Room(const LoggedUser & creator, const RoomData & data);
    
    Room& operator=(const Room& other);
	int addUser(const LoggedUser & user);
	void removeUser(const LoggedUser & user);
	std::vector<std::string> getAllUsers() ;
    RoomData& getRoomData();
  
    
};