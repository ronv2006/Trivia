#include "Server.h"
#include <thread>
#include <string>
#include <iostream>
#include "SqliteDatabase.h"
Server::Server(std::shared_ptr<IDatabase>& db) : m_database(db), m_handlerFactory(db), _communicator(this->m_handlerFactory)
{




}

void Server::run()
{
    std::thread t_communicator(&Communicator::startHandleRequests, std::ref(this->_communicator));
    t_communicator.detach();
    std::string str = "";


    while (str != "EXIT") {
        std::cin >> str;
        std::cout << str << std::endl;
    }
}

