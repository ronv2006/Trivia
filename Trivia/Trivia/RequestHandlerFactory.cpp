#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(std::weak_ptr<IDatabase> db) : m_loginManager(db), m_database(db), m_statisticManager(db)
{
   

}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
    return std::make_unique<LoginRequestHandler>(*this);
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user, RequestHandlerFactory& factory)
{
    return std::make_unique<MenuRequestHandler>(user,factory);
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(Room& room, LoggedUser& admin, RoomManager& roomManager, RequestHandlerFactory& factory)
{
    return std::make_unique<RoomAdminRequestHandler>(room, admin, roomManager,factory);
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& factory)
{
    return std::make_unique<RoomMemberRequestHandler>(room, user, roomManager, factory);
}

StatisticManager& RequestHandlerFactory::getStatisticManager()
{
    return this->m_statisticManager;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return this->m_roomManager;
}
