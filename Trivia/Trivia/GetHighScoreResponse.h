#pragma once
#include <string>
#include <vector>

class GetHighScoreResponse {
public:
    unsigned int status;
    std::vector<std::string> statistics;
};