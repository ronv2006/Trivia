#pragma once
#include "RoomData.h"
#include "Room.h"
#include <map>
#include <functional>

#include <mutex>
class RoomManager {
private:
    std::map<std::string, Room> m_rooms;
    std::mutex m_roomsMutex;
   
public:
    void createRoom(LoggedUser& creator,RoomData& data);
    void deleteRoom(const std::string name);
    unsigned int getRoomState(const std::string name);
    std::vector<RoomData> getRooms();
    Room& getRoom(const std::string roomName);
    
    
    
    
};