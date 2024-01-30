#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"

#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomMemberRequestHandler : public IRequestHandler {
private:
    Room& m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
public:
    RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& factory);
    bool isRequestRelevent(const RequestInfo& request) const override;
    RequestResult handleRequest(const RequestInfo& request);
    RequestResult leaveGame(const RequestInfo& request);
    RequestResult getRoomState(const RequestInfo& request);
};