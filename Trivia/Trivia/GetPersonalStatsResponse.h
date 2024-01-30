#pragma once
#include <vector>
#include <string>

class GetPersonalStatsResponse {
public:
    unsigned int status;
    std::vector<std::string> statistics;
};
