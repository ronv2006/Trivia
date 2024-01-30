#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
class Server {
public:
    Server(std::shared_ptr<IDatabase>& db);
    void run();

private:

    std::shared_ptr<IDatabase> m_database;
    RequestHandlerFactory m_handlerFactory;
    Communicator _communicator;
};
