#include "Server.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstddef>
// #include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>

Server::Server()
{
    if (getSocket() != 0)
    {
        std::cout << std::format("Failed to start server with PORT: {}", m_service);
    }
}

Server::Server(const char* IP, const char* port)
{
    if (getSocket(IP, port) != 0)
    {
        std::cout << std::format("Failed to start server with PORT: {}", m_service);
    }
}

Server::~Server() { stopServer(); }

void Server::stopServer()
{
    close(m_sockfd);
    close(m_newSocket);
}

int Server::getSocket(const char* IP, const char* port)
{
    int status{};
    int yes{1};

    // RAII for raw_res to deallocate linked list when out of scope
    std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> res(nullptr, &freeaddrinfo);
    struct addrinfo hints{}, *raw_res{nullptr};  // Pointer to linked list of valid addrinfo

    hints.ai_family   = AF_UNSPEC;    // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets
    hints.ai_flags    = AI_PASSIVE;   // fill in my IP for me

    if ((status = getaddrinfo(IP, port, &hints, &raw_res)) != 0)
    {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        return status;
    }

    res.reset(raw_res);  // RAII for pointer to linked list

    for (addrinfo* p = res.get(); p != nullptr; p = p->ai_next)
    {
        if ((m_sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        // Auto unbinds old sockets to port. Should allow instant reuse when rerunning. If
        // setsockopt not here, could have to wait for socket to unbind
        if ((status = setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
        {
            perror("setsockopt");
            return status;
        }

        if (bind(m_sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(m_sockfd);
            perror("server: bind");
            continue;
        }

        if (getnameinfo(p->ai_addr, p->ai_addrlen, m_host, sizeof(m_host), m_service,
                        sizeof(m_service), NI_NUMERICHOST | NI_NUMERICSERV))
        {
            printf("could not resolve hostname");
        }
        break;
    }
    return status;
}

void Server::startListen()
{
    if (listen(m_sockfd, 20) < 0)
    {
        printf("Socket listen failed");
        return;
    }

    printf("\n*** Listening on ADDRESS: %s, PORT: %s ***\n", m_host, m_service);

    while (true)
    {
        printf("====== Waiting for a new connection ======\n\n");
        acceptConnection(m_newSocket);

        char buffer[BUFFER_SIZE]{};

        ssize_t bytesReceived = recv(m_newSocket, buffer, BUFFER_SIZE, 0);

        if (bytesReceived < 0)
        {
            printf("Failed to read bytes from client socket connection");
        }

        printf("------ Received Request from client ------\n");
        printf("%s \n", buffer);
        sendResponse();

        close(m_newSocket);
    }
}

void Server::acceptConnection(int& newSocket)
{
    struct sockaddr_storage their_addr;

    socklen_t addr_size = static_cast<socklen_t>(sizeof(their_addr));

    newSocket = accept(m_sockfd, (struct sockaddr*)&their_addr, &addr_size);

    if (newSocket < 0)
    {
        printf("Server failed to accept incoming connection from ADDRESS: %s, PORT: %s \n", m_host,
               m_service);
    }
}

std::string Server::buildResponse()
{
    std::string htmlFile =
        "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) "
        "</p></body></html>";
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
       << htmlFile;

    return ss.str();
}

void Server::sendResponse()
{
    auto   response  = buildResponse();
    size_t bytesSent = send(m_newSocket, response.c_str(), response.size(), 0);

    if (bytesSent == response.size())
    {
        printf("------ Server Response sent to client ------\n\n");
    }
    else
    {
        printf("Error sending response to client");
    }
}
