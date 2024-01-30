#pragma once

#include "IRequestHandler.h"
#include "StatisticManager.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "Protocol.h"
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {
public:
    MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& factory);
    bool isRequestRelevent(const RequestInfo& ri)const override;
    RequestResult handleRequest(const RequestInfo& ri) override;
    RequestResult signout(const RequestInfo& info);
    RequestResult getRooms(const RequestInfo& info);
    RequestResult getPlayersInRoom(const RequestInfo& info);
    RequestResult getPersonalStats(const RequestInfo& info);
    RequestResult getHighScore(const RequestInfo& info);
    RequestResult joinRoom(const RequestInfo& info);
    RequestResult createRoom(const RequestInfo& info);
    ~MenuRequestHandler() = default;
private:
    LoggedUser m_user;
    RequestHandlerFactory& m_handlerFactory;
    static unsigned int _nextRoomId;
    mutable std::mutex _countMutex;
};
