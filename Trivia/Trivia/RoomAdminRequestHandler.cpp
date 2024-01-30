#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& factory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(factory)
{
}
bool RoomAdminRequestHandler::isRequestRelevent(const RequestInfo& request) const
{
    switch (request.id) {
    case(CLOSE_ROOM_REQUEST): {
        break;
    }
    case(START_GAME_REQUEST): {
        break;
    }
    case(GET_ROOM_STATE_REQUEST): {
        break;
    }
    
    default:
    {
        return false;
    }
    }
    return true;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
{
    RequestResult error;
    if (!isRequestRelevent(request)) {
        ErrorResponse err;
        error.m_buffer = JsonResponsePacketSerializer::serializeResponse(err);
        error.m_newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_room,this->m_user, this->m_roomManager, this->m_handlerFactory);
    }
    RequestResult result;
    switch (request.id) {
    case(CLOSE_ROOM_REQUEST): {
       return closeRoom(request);
    }
    case(START_GAME_REQUEST): {
        return startGame(request);
    }
    case(GET_ROOM_STATE_REQUEST): {
        return getRoomState(request);
    }
    
    }
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& request)
{
    RequestResult result;
    CloseRoomResponse response;
    
    this->m_roomManager.deleteRoom(this->m_room.getRoomData().name);
    response.status = 1;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(response);
    result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& request)
{
    RequestResult result;
    StartGameResponse response;
    
    response.status = 1;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(response);
    result.m_newHandler = nullptr; // will be GameRequestHandler
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& request)
{
    try{
        auto & room = this->m_roomManager.getRoom(this->m_room.getRoomData().name);
    }
        catch (...) {
        RequestResult result;
        GetRoomStateResponse response;
        response.status = 42;
        result.m_buffer = JsonResponsePacketSerializer::serializeResponse(response);
        result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
        return result;
    }
    RequestResult result;
    GetRoomStateResponse response;
    RoomData& data = this->m_room.getRoomData();
    response.answerTimeOut = data.timePerQuestion;
    response.hasGameBegun = data.isActive;
    response.players = this->m_room.getAllUsers();
    response.questionCount = data.numOfQuestionsInGame;

    response.status = 1;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(response);
    result.m_newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_room, this->m_user, this->m_roomManager, this->m_handlerFactory);
    return result;
}
