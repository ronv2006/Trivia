#include "MenuRequestHandler.h"

#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "GetRoomsResponse.h"
#include <memory>

unsigned int MenuRequestHandler::_nextRoomId = 1;

MenuRequestHandler::MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& factory) : m_user(user), m_handlerFactory(factory)
{
    
    
}

bool MenuRequestHandler::isRequestRelevent(const RequestInfo& ri) const
{
    switch (ri.id) {
    case(GET_PLAYERS_REQUEST): {
        break;
        }
    case(GET_ROOMS_REQUEST): {
        break;
    }
        
    case(CREATE_ROOM_REQUEST):{
            break;
        }
    case(JOIN_ROOM_REQUEST): {
        break;
    }
    case(LOGOUT_REQUEST): {
        break;
    }
    case(PERSONAL_STAT_REQUEST): {
         break;
    }
    case(HIGHEST_SCORES_REQUEST): {
        break;
    }
    default: {
        return false;
    }
           
    }
    return true;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& ri)
{
    RequestResult result;
    if (!isRequestRelevent(ri)) {
        ErrorResponse error;
        error.message = "Invalid request";
        result.m_buffer = JsonResponsePacketSerializer::serializeResponse(error);
        result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
        return result;
    }
    switch (ri.id) {
    case(LOGOUT_REQUEST): {
        return signout(ri);
    }
    case(GET_PLAYERS_REQUEST): {
        return getPlayersInRoom(ri);
    }
    case(CREATE_ROOM_REQUEST): {
        return createRoom(ri);
    }
    case(JOIN_ROOM_REQUEST): {
        return joinRoom(ri);
    }
    case(PERSONAL_STAT_REQUEST): {

        return getPersonalStats(ri);

    }
    case(HIGHEST_SCORES_REQUEST): {
        return getHighScore(ri);
    }
    case(GET_ROOMS_REQUEST): {
        return getRooms(ri);
    }
    }
    return RequestResult();
}

RequestResult MenuRequestHandler::signout(const RequestInfo& info)
{
    RequestResult result;
    LogoutResponse logout;
    logout.status = 1;
    std::string username = this->m_user.getUsername();
    this->m_handlerFactory.getLoginManager().logout(username);
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(logout);
    result.m_newHandler = this->m_handlerFactory.createLoginRequestHandler();

    return result;
    
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& info)
{
    RequestResult result;
    GetRoomsReponse roomsResponse;
    roomsResponse.status = 1;
    roomsResponse.rooms = this->m_handlerFactory.getRoomManager().getRooms();
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(roomsResponse);
    result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& info)
{
    RequestResult result;
    GetPlayersInRoomResponse playerInRoomResponse;
    GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.m_buffer);
    playerInRoomResponse.players = this->m_handlerFactory.getRoomManager().getRoom(request.roomName).getAllUsers();
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(playerInRoomResponse);
    result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info)
{
    
    RequestResult result;
    GetPersonalStatsResponse personalStatsResponse;
    personalStatsResponse.statistics = this->m_handlerFactory.getStatisticManager().getUserStatistics(this->m_user.getUsername());
    personalStatsResponse.status = 1;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(personalStatsResponse);
    result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    return result;
   
    
    
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info)
{
    RequestResult result;
    GetHighScoreResponse highScoreResponse;
    highScoreResponse.statistics = this->m_handlerFactory.getStatisticManager().getHighScores();
    highScoreResponse.status = 1;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(highScoreResponse);
    result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info)
{
    RequestResult result;
    JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.m_buffer);
    JoinRoomResponse joinRoomResponse;
    
    Room& room = this->m_handlerFactory.getRoomManager().getRoom(request.name);
    joinRoomResponse.status = this->m_handlerFactory.getRoomManager().getRoom(request.name).addUser(this->m_user);
    if (joinRoomResponse.status == 0) {
        result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    }
    else
    {
        result.m_newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(room, this->m_user, this->m_handlerFactory.getRoomManager(), this->m_handlerFactory);
    }
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);
    return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& info)
{
    RequestResult result;
    CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.m_buffer);
    CreateRoomResponse createRoomResponse;
    createRoomResponse.status = 1;
   
    RoomData roomData;
    roomData._id = this->_nextRoomId;
    this->_nextRoomId++;
    roomData.isActive = true;
    roomData.maxPlayers = request.maxUsers;
    roomData.name = request.roomName;
    roomData.numOfQuestionsInGame = request.questionCount;
    roomData.timePerQuestion = request.answerTimeout;
    
    this->m_handlerFactory.getRoomManager().createRoom(this->m_user, roomData);
    createRoomResponse.status = 1;
    createRoomResponse.roomId = roomData._id;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(createRoomResponse);
    Room& room = this->m_handlerFactory.getRoomManager().getRoom(roomData.name);
    result.m_newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(room, this->m_user, this->m_handlerFactory.getRoomManager(), this->m_handlerFactory);
    return result;
}
