#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "Protocol.h"



std::vector<unsigned char> jsonToVectorOfChars(nlohmann::json jsonBuffer) {
    std::string strBuffer = jsonBuffer.dump();
    std::vector<unsigned char> m_buffer;
    m_buffer.assign(strBuffer.begin(), strBuffer.end());
    return m_buffer;
}


std::vector<unsigned char> addSizeToVector(std::vector<unsigned char> vectorBuffer, int sizeOfMessage)
{   
    vectorBuffer.insert(vectorBuffer.begin(), static_cast<char>(sizeOfMessage & 0xFF));
    vectorBuffer.insert(vectorBuffer.begin(), static_cast<char>((sizeOfMessage >> 8) & 0xFF));
    vectorBuffer.insert(vectorBuffer.begin(), static_cast<char>((sizeOfMessage >> 16) & 0xFF));
    vectorBuffer.insert(vectorBuffer.begin(), static_cast<char>((sizeOfMessage >> 24) & 0xFF));
    
    
   

    return vectorBuffer;
}

std::vector<unsigned char> createStatusResponse(int status, responseStatus response) {
    nlohmann::json jsonData = { {"Status", status} };


    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), response);

    return vectorBuffer;
}


std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& err)
{
    nlohmann::json jsonData = { {err.message} };
    

    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), ERRORMSG_RESPONSE);

    return vectorBuffer;
    

}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LoginResponse& log)
{
    
    return createStatusResponse(log.status, LOGIN_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& sign)
{
  

    return createStatusResponse(sign.status, SIGNUP_RESPONSE);
    
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
    
    
    return createStatusResponse(response.status, LOGOUT_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetRoomsReponse& response)
{
    nlohmann::json jsonData;
    if (response.status == 0) {
        return createStatusResponse(response.status, GET_ROOMS_RESPONSE);
    }
    else
    {
        std::string rooms = "";
        for (auto& it : response.rooms) {
            rooms = rooms + it.name + ",";
        }
        rooms = rooms.substr(0, rooms.length() - 1); // remove the last ,
        jsonData = { {"Rooms", rooms} };
    }
    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), GET_ROOMS_RESPONSE);
    return vectorBuffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
    nlohmann::json jsonData;
    std::string users = "";
    for (auto& it : response.players) {
        users = users + it + ",";
    }
    users = users.substr(0, users.length() - 1);
    jsonData = { {"Users", users} };
    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), GET_PLAYERS_IN_ROOM_RESPONSE);
    return vectorBuffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
    return createStatusResponse(response.status, JOIN_ROOM_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
    return createStatusResponse(response.status, CREATE_ROOM_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
    std::string highScoreString = "";
    for (auto& it : response.statistics) {
        highScoreString = highScoreString + it + ",";
    }
    highScoreString = highScoreString.substr(0, highScoreString.length() - 1); // remove the last ,
    nlohmann::json jsonData = { {"HighScore", highScoreString} };
    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), GET_PLAYERS_IN_ROOM_RESPONSE);
    return vectorBuffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
    nlohmann::json jsonData = { {"NumOfPlayerGames", response.statistics[3]}, {"NumOfTotalAnswers", response.statistics[2]}, {"NumOfCorrectAnswers", response.statistics[1]}, {"PlayerAverageTime", response.statistics[0]} };
    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), PERSONAL_STATS_RESPONSE);
    return vectorBuffer;

}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
    return createStatusResponse(response.status, CLOSE_ROOM_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
{
    return createStatusResponse(response.status, START_GAME_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
    if (response.status == 0) {
        return createStatusResponse(0, GET_ROOM_STATE_RESPONSE);
    }

    std::string players = "";
    for (auto& it : response.players) {
        players = players + it + ",";
    }
    players = players.substr(0, players.length() - 1);
    
    nlohmann::json jsonData = { {"Status", response.status}, {"QuestionCount", response.questionCount}, {"HasGameBegan", response.hasGameBegun}, {"Players", players}, {"AnswerTimeout", response.answerTimeOut} };
    std::vector<unsigned char> vectorBuffer = jsonToVectorOfChars(jsonData);
    int sizeOfMessage = vectorBuffer.size();
    vectorBuffer = addSizeToVector(vectorBuffer, sizeOfMessage);
    vectorBuffer.insert(vectorBuffer.begin(), GET_ROOM_STATE_RESPONSE);
    return vectorBuffer;

}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
    return createStatusResponse(response.status, LEAVE_ROOM_RESPONSE);

}



