#include "RoomMemberRequestHandler.h"
#include "LeaveRoomResponse.h";
#include "JsonResponsePacketSerializer.h";
RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& factory): m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(factory)
{
    
}

bool RoomMemberRequestHandler::isRequestRelevent(const RequestInfo& request) const
{
    switch (request.id) {
    case(LEAVE_ROOM_REQUEST): {
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

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& request)
{
    if (!isRequestRelevent(request)) {
        ErrorResponse err;
        RequestResult result;
        result.m_buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.m_newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_room, this->m_user, this->m_roomManager, this->m_handlerFactory);
        return result;
    }
    switch (request.id) {
    case(LEAVE_ROOM_REQUEST): {
        return leaveGame(request);
    }
    case(GET_ROOM_STATE_REQUEST): {
        return getRoomState(request);
    }
    }
    return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveGame(const RequestInfo& request)
{
    RequestResult result;
    LeaveRoomResponse response;
    this->m_roomManager.getRoom(this->m_room.getRoomData().name).removeUser(this->m_user);
    response.status = 1;
    result.m_buffer = JsonResponsePacketSerializer::serializeResponse(response);
    result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& request)
{
    try {
        auto& room = this->m_roomManager.getRoom(this->m_room.getRoomData().name);
    }
    catch (...) {
        RequestResult result;
        result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user, this->m_handlerFactory);
        GetRoomStateResponse response;



        response.status = 42;
        result.m_buffer = JsonResponsePacketSerializer::serializeResponse(response);
        result.m_newHandler = this->m_handlerFactory.createMenuRequestHandler( this->m_user, this->m_handlerFactory);
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
    result.m_newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_room, this->m_user, this->m_roomManager, this->m_handlerFactory);
    return result;
}
