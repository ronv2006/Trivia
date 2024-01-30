#include "LoginRequestHandler.h"

#include "Protocol.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <WinSock2.h>


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& requestHandlerFactory) : m_handlerFactory(requestHandlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevent(const RequestInfo& request) const
{
    switch (request.id) {
    case(LOGIN_REQUEST): {
        return true;
    }

    case(SIGNUP_REQUEST): {
        return true;
    }
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request)
{

    switch (request.id) {
    case LOGIN_REQUEST:
    {
        return login(request);



        break;
    }
    case SIGNUP_REQUEST:
    {

        return signup(request);



        break;
    }
    
    }



}

RequestResult LoginRequestHandler::login(const RequestInfo& request) const
{
    std::vector<unsigned char> cutBuffer(request.m_buffer.begin() + 5, request.m_buffer.end());
    LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(cutBuffer);
    bool isLoginSuccsessful = this->m_handlerFactory.getLoginManager().login(loginRequest.username, loginRequest.password);
    LoginResponse response;

    response.status = isLoginSuccsessful;
    std::vector<unsigned char> bufferResponse = JsonResponsePacketSerializer::serializeResponse(response);
    if (isLoginSuccsessful) {
        LoggedUser loggedUser(loginRequest.username);
        return RequestResult{ bufferResponse, this->m_handlerFactory.createMenuRequestHandler(loggedUser,this->m_handlerFactory) };

    }
    else
    {
        return RequestResult{ bufferResponse, this->m_handlerFactory.createLoginRequestHandler() };
    }



}

RequestResult LoginRequestHandler::signup(const RequestInfo& request) const
{

    std::vector<unsigned char> cutBuffer(request.m_buffer.begin() + 5, request.m_buffer.end());

    SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(cutBuffer);
    bool isSignupSuccsessful = this->m_handlerFactory.getLoginManager().signup(signupRequest.username, signupRequest.password, signupRequest.email);
    LoginResponse response;
    response.status = isSignupSuccsessful;
    std::vector<unsigned char> bufferResponse = JsonResponsePacketSerializer::serializeResponse(response);
    if (isSignupSuccsessful) {
        LoggedUser user(signupRequest.username);
        return RequestResult{ bufferResponse, this->m_handlerFactory.createMenuRequestHandler(user,this->m_handlerFactory)};

    }
    else
    {
        return RequestResult{ bufferResponse, this->m_handlerFactory.createLoginRequestHandler() };
    }


}

