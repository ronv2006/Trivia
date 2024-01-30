#include "Communicator.h"
#include <iostream>
#include "LoginRequestHandler.h"
#pragma comment (lib, "ws2_32.lib")
#include "Protocol.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <thread>
#include "SqliteDatabase.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("WSAStartup failed with error: %d\n", result);

    }



    // this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
    // if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
    this->_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bindAndListen();

    if (this->_serverSocket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__ " - socket");



}

void Communicator::startHandleRequests()
{
    while (true) {
        // this accepts the client and create a specific socket from server to this client
    // the process will not continue until a client connects to the server
        SOCKET client_socket = accept(_serverSocket, NULL, NULL);
        if (client_socket == INVALID_SOCKET)
            throw std::exception(__FUNCTION__);

        std::cout << "Client accepted. Server and client can speak" << std::endl;
        // the function that handle the conversation with the client
        std::thread t_handleNewClient(&Communicator::handleNewClient, this, client_socket);
        t_handleNewClient.detach();
    }

}

void Communicator::bindAndListen()
{
    struct sockaddr_in sa = { 0 };
    this->_port = 8824;

    sa.sin_port = htons(this->_port); // port that server will listen for
    sa.sin_family = AF_INET;   // must be AF_INET
    sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

    // Connects between the socket and the configuration (port and etc..)
    if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR) {
        std::cout << WSAGetLastError() << std::endl;
        throw std::exception(__FUNCTION__ " - bind");
    }

    // Start listening for incoming requests of clients
    if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << WSAGetLastError() << std::endl;
        throw std::exception(__FUNCTION__ " - listen");
    }
    std::cout << "Listening on port " << this->_port << std::endl;
}

void Communicator::handleNewClient(SOCKET socket)
{
    std::cout << "New client detected" << std::endl;
    this->_clients.insert(std::make_pair(socket, this->m_handlerFactory.createLoginRequestHandler()));

    char m_buffer[1024];

    int bytesRecieved = recv(socket, m_buffer, sizeof(m_buffer), 0);
    time_t currentTime = time(0);

    while (this->_clients.at(socket).get() != nullptr)
    {


        if (bytesRecieved == SOCKET_ERROR) {
            this->_clients.at(socket) = nullptr;
        }
        else if (bytesRecieved == 0) {
            this->_clients.at(socket) = nullptr;
        }
        else {
            m_buffer[bytesRecieved] = 0;
            
            
            std::vector<unsigned char> vecBuffer(m_buffer, m_buffer + bytesRecieved);
            RequestInfo requestInfo = { m_buffer[0], currentTime, vecBuffer };
            RequestResult result = this->_clients.at(socket).get()->handleRequest(requestInfo);
            this->_clients.at(socket) = std::move(result.m_newHandler);
            unsigned char* responseBuff = result.m_buffer.data();
            char* sendableResponse = reinterpret_cast<char*>(responseBuff);
            send(socket, sendableResponse, result.m_buffer.size(), 0);


        }
         bytesRecieved = recv(socket, m_buffer, sizeof(m_buffer), 0);
         std::string str(m_buffer);

        time_t currentTime = time(0);
    }
}

