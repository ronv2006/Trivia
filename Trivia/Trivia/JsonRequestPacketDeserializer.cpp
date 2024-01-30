#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <iostream>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& m_buffer)
{
    std::string stringBuffer(m_buffer.begin(), m_buffer.end());
    nlohmann::json jsonBuffer = nlohmann::json::parse(stringBuffer);
    LoginRequest lr;
     
    
    lr.username = jsonBuffer.at("Username");
    lr.password = jsonBuffer.at("Password");
    return lr;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& m_buffer)
{
    std::string stringBuffer(m_buffer.begin(), m_buffer.end());
   
    nlohmann::json jsonBuffer = nlohmann::json::parse(stringBuffer);
    SignupRequest sr;
    sr.username = jsonBuffer.at("Username");
    sr.password = jsonBuffer.at("Password");
    sr.email = jsonBuffer.at("Email");
    return sr;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer)
{
    std::string stringBuffer(buffer.begin(), buffer.end());
    nlohmann::json jsonBuffer = nlohmann::json::parse(stringBuffer);
    GetPlayersInRoomRequest request;
    request.roomName = jsonBuffer["RoomName"];
    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer)
{
    std::string stringBuffer(buffer.begin() + 5, buffer.end());
    nlohmann::json jsonBuffer = nlohmann::json::parse(stringBuffer);
    JoinRoomRequest request;
    request.name = jsonBuffer["RoomName"];
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer)
{
    std::string stringBuffer(buffer.begin() + 5, buffer.end());
    nlohmann::json jsonBuffer = nlohmann::json::parse(stringBuffer);
    CreateRoomRequest request;
    std::string answerTimeout = jsonBuffer["AnswerTimeout"];
    request.answerTimeout = std::stoi(answerTimeout);
    std::string maxUsers = jsonBuffer["MaxUsers"];
    request.maxUsers = std::stoi(maxUsers);
    std::string questionCount= jsonBuffer["QuestionCount"];
    request.questionCount = std::stoi(questionCount);
    request.roomName =  jsonBuffer["Name"];
    return request;
    
    
    
}
