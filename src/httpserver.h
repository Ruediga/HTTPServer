#pragma once

#include "tcpserver.h"
#include "httprequest.h"

#include <map>

class HTTPServer : public TCPServer
{
public:
    HTTPServer(const char *name, int port);

    std::string p_HandleRequest(std::string& data_in) override;

    void startup() override;

    ~HTTPServer() override {}

protected:
    std::map<std::string, std::string> p_headers {
        {"Server", "Munki-HTTPServer"},
        {"Content-Type", "text/html"}
    };
    std::map<int, std::string> p_status_codes {
        {200, "OK"},
        {404, "Not Found"},
        {501, "Not Implemented"}
    };
    
    std::string response_line(int status_code);
    std::string response_headers(std::map<std::string, std::string> &extraHeaders);
    std::string response_OPTIONS_handler(HTTPRequest &request);
    std::string response_GET_handler(HTTPRequest &request);
    std::string response_HTTP_501_handler(HTTPRequest &request);
};