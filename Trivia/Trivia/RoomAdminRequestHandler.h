#pragma once
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "Protocol.h"

class RequestHandlerFactory;
class RoomAdminRequestHandler : public IRequestHandler {
private:
    Room& m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
public:
    RoomAdminRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& factory);
    bool isRequestRelevent(const RequestInfo& request) const override;
    RequestResult handleRequest(const RequestInfo& request);
    RequestResult closeRoom(const RequestInfo& request);
    RequestResult startGame(const RequestInfo& request);
    RequestResult getRoomState(const RequestInfo& request);
};