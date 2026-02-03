#ifndef BD422DF4_F897_4555_89D2_D103D95674F7
#define BD422DF4_F897_4555_89D2_D103D95674F7

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string>

constexpr size_t BUFFER_SIZE{3000};

class Server
{
 public:
    Server();
    Server(const char* IP, const char* port);

    Server(const Server&) = delete;
    Server(Server&&)      = delete;

    ~Server();

    void startListen();
    void stopServer();

 private:
    int  getSocket(const char* IP = nullptr, const char* port = "8080");
    void acceptConnection(int& new_socket);

    std::string buildResponse();
    void        sendResponse();

    char m_host[NI_MAXHOST];
    char m_service[NI_MAXSERV];

    int m_sockfd;
    int m_newSocket;
};

#endif /* BD422DF4_F897_4555_89D2_D103D95674F7 */
