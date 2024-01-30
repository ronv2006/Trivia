#pragma once
#include <vector>
#include <string>
class GetRoomStateResponse {
public:
    unsigned int status;
    bool hasGameBegun;
    std::vector<std::string> players;
    unsigned int questionCount;
    float answerTimeOut;

};