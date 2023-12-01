#pragma once

#include <string>

class TCPServer
{
public:
    TCPServer(const char *name, int port);
    virtual ~TCPServer() {}

    virtual void startup();

    // override
    virtual std::string p_HandleRequest(std::string& data_in);

protected:
    std::string p_host_name;
    int p_port;
};