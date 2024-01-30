#pragma once
#include <vector>
#include "IRequestHandler.h"
#include <memory>
class IRequestHandler;
class RequestResult {
public:
    //RequestResult(std::vector<unsigned char>& buffer, std::unique_ptr<IRequestHandler>& handler);
    std::vector<unsigned char> m_buffer;
    std::unique_ptr<IRequestHandler> m_newHandler;
};
