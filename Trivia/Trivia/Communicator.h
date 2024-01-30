#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"
#include <memory>
#include "RequestHandlerFactory.h"
class Communicator {
public:
    Communicator(RequestHandlerFactory& handlerFactory);
    void startHandleRequests();
    void bindAndListen();
    void handleNewClient(SOCKET socket);
private:
    SOCKET _serverSocket;
    std::map<SOCKET, std::unique_ptr<IRequestHandler>> _clients;
    int _port;
    RequestHandlerFactory& m_handlerFactory;
};
