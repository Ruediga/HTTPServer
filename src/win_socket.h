#pragma once

#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h> // include before <windows.h> to avoid compilation problems
#include <ws2tcpip.h> // more modern (API WARNINGS DEPRECATED)
#include <windows.h>
#include <io.h>

#include <string>

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

namespace Settings
{
    // max connections with the server
    const int MAXCONNECTIONS = 5;
    // max data that can be received at once in bytes (avoid data being capped by OS)
    const int MAXRECV = 1024;
}

class Socket
{
public:
    Socket();
    virtual ~Socket();
    // TCP
    bool create();
    // UDP
    bool UDP_create();
    bool bind(const int port);
    bool listen() const;
    bool accept(Socket &new_socket, std::string &connectionIP) const;
    bool connect(const std::string host, const int port);
    // TCP
    bool send(const std::string) const;
    int recv(std::string &) const;
    // UDP
    bool UDP_send(const std::string, const std::string,
                  const int port) const;
    int UDP_recv(std::string &) const;
    // close socket
    bool close() const;
    // WSAcleanup()
    void cleanup() const;
    bool is_valid() const { return m_sock != -1; }
    int get_m_sock() const { return m_sock; }
    void set_m_sock(int nr) { m_sock = nr; }

private:
    // socket descriptor
    int m_sock;
    // struct sockaddr_in
    sockaddr_in m_addr;
};