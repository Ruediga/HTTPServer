#include "tcpserver.h"

#include <iostream>

TCPServer::TCPServer(const char *name, int port)
    : p_host_name{name}, p_port{port}
{}

void TCPServer::startup()
{
    // empty
}

std::string TCPServer::p_HandleRequest(std::string& data_in)
{
    std::string str{};
    
    return str;
}