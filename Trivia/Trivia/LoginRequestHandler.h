#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
private:
    
    RequestHandlerFactory& m_handlerFactory;
public:

    LoginRequestHandler(RequestHandlerFactory& requestHandlerFactory);
    bool isRequestRelevent(const RequestInfo& request) const override;
    RequestResult handleRequest(const RequestInfo& request)override;
    RequestResult login(const RequestInfo& request) const;
    RequestResult signup(const RequestInfo& request) const;
};
