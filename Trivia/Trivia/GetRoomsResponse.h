#pragma once
#include <vector>
#include "RoomData.h"

class GetRoomsReponse {
public:
    unsigned int status;
    std::vector<RoomData> rooms;
};