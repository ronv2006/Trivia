#include "RoomManager.h"



void RoomManager::createRoom(LoggedUser& creator, RoomData& data)
{
    std::lock_guard<std::mutex> guard(this->m_roomsMutex);
    Room room(creator, data);
    m_rooms[data.name] = room;
}

void RoomManager::deleteRoom(const std::string roomName)
{
    std::lock_guard<std::mutex> guard(this->m_roomsMutex);
    this->m_rooms.erase(roomName);
}

unsigned int RoomManager::getRoomState(const std::string roomName)
{
    std::lock_guard<std::mutex> guard(this->m_roomsMutex);
    return this->m_rooms.at(roomName).getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()

{
    std::lock_guard<std::mutex> guard(this->m_roomsMutex);
    std::vector<RoomData> rooms;
    for (auto& it : this->m_rooms) {
        rooms.push_back(it.second.getRoomData());
    }
    return rooms;
}

Room& RoomManager::getRoom(const std::string roomName)
{
    std::lock_guard<std::mutex> guard(this->m_roomsMutex);
    return this->m_rooms.at(roomName);
   
}



//unsigned int& RoomManager::getNextRoomId()
//{
//    std::lock_guard<std::mutex> guard(this->_countMutex);
//    this->_count++; // start from 0 so the first id will be 1
//    return this->_count;
//}
