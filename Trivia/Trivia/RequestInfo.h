#pragma once
#include <ctime>
#include <vector>
class RequestInfo {
public:
    unsigned char id;
    std::time_t recievedtime;
    std::vector<unsigned char> m_buffer;

};
