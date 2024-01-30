#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"
class RequestResult;
class IRequestHandler {
public:
    virtual bool isRequestRelevent(const RequestInfo& ri)const = 0;
    virtual RequestResult handleRequest(const RequestInfo& ri) = 0;
    virtual ~IRequestHandler() = default;
};
