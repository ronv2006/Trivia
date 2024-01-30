#pragma once

#include "LoginManager.h"
#include <memory>
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "StatisticManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory {
private:
    LoginManager m_loginManager;
    std::weak_ptr<IDatabase> m_database;
    RoomManager m_roomManager;
    StatisticManager m_statisticManager;
public:
    RequestHandlerFactory(std::weak_ptr<IDatabase> db);
    std::unique_ptr<IRequestHandler> createLoginRequestHandler();
    std::unique_ptr<IRequestHandler> createMenuRequestHandler(LoggedUser& user, RequestHandlerFactory& factory);
    std::unique_ptr<IRequestHandler> createRoomAdminRequestHandler(Room& room, LoggedUser& admin, RoomManager& roomManager, RequestHandlerFactory& factory);
    std::unique_ptr<IRequestHandler> createRoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& factory);
    LoginManager& getLoginManager();
    RoomManager& getRoomManager();
    StatisticManager& getStatisticManager();

};
