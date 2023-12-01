#pragma once

#include <string>

class HTTPRequest
{
public:
    HTTPRequest(std::string& data);

    std::string m_method;
    std::string m_uri;
    std::string m_http_version;

    void p_Parse(std::string& data);
};