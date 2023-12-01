#include "httprequest.h"

#include <iostream>
#include <vector>
#include <sstream>

void HTTPRequest::p_Parse(std::string &data)
{
    std::vector<std::string> lines;
    std::istringstream ss(data);

    // Splitting data into lines
    std::string line;
    while (std::getline(ss, line, '\r'))
    {
        lines.push_back(line);
    }

    // Getting the request line
    std::string request_line = lines[0];

    // Splitting request line into words
    std::istringstream request_ss(request_line);
    std::vector<std::string> words;
    std::string word;
    while (std::getline(request_ss, word, ' '))
    {
        words.push_back(word);
    }

    m_method = words[0];

    if (words.size() > 1)
    {
        m_uri = words[1];
    }

    if (words.size() > 2)
    {
        m_http_version = words[2];
    }
}

HTTPRequest::HTTPRequest(std::string &data)
    : m_method{""}, m_uri{""}, m_http_version{"1.1"}
{
    p_Parse(data);
}
