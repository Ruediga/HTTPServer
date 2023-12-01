#include "httpserver.h"
#include "httprequest.h"
#include "defaults.h"
#include "util.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "win_socket.h"
#endif
#ifdef _WIN64
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "win_socket.h"
#endif
#ifdef __linux__
#include "linux_socket.h"
#endif

// thanks to https://github.com/lasselukkari/MimeTypes for making this utility
#include "MimeTypes.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

// global
const std::string blank_line = "\r\n";

HTTPServer::HTTPServer(const char *name, int port)
    : TCPServer(name, port)
{
    removeFile(DEFAULT_LOGGING_PATH);

    defaultLog("Server initialized\n");
}

std::string HTTPServer::p_HandleRequest(std::string& data_in)
{
    HTTPRequest request = {data_in};

    std::string response;

    if (request.m_method == "OPTIONS")
        response = response_OPTIONS_handler(request);
    else if (request.m_method == "GET")
        response = response_GET_handler(request);
    else
        response = response_HTTP_501_handler(request);

    return response;
}

void HTTPServer::startup()
{
    Socket serverSocket;

    serverSocket.create();
    serverSocket.bind(p_port);
    serverSocket.listen();

    std::cout << "Listening on port " << p_port << '\n';

    while (1)
    {
        Socket connection;
        std::string connectedIP;

        serverSocket.accept(connection, connectedIP);
        std::string connection_msg = "Connected by " + connectedIP + '\n';
        defaultLog("\n", true);
        defaultLog(connection_msg);

        std::string data_in;
        // change macro MAXRECV to get more bytes
        connection.recv(data_in);

        std::string data_out = p_HandleRequest(data_in);

        connection.send(data_out);
        connection.close();
    }
}

std::string HTTPServer::response_line(int status_code)
{
    std::string reason = p_status_codes[status_code];
    // [TODO] fix HTTP/1.1 hardcoded
    std::string response_line = {"HTTP/1.1 " + std::to_string(status_code) + ' ' + reason + blank_line};
    return response_line;
}

std::string HTTPServer::response_headers(std::map<std::string, std::string> &extraHeaders)
{
    std::map<std::string, std::string> headersCopy = extraHeaders;

    // Merge extra_headers with headers_copy
    for (const auto& extraHeader : extraHeaders) {
        headersCopy[extraHeader.first] = extraHeader.second;
    }

     std::string headersStr;

    // Constructing the headers string
    for (const auto& header : headersCopy) {
        headersStr += header.first + ": " + header.second + blank_line;
    }

    return headersStr;
}

std::string HTTPServer::response_OPTIONS_handler(HTTPRequest &request)
{
    std::string responseLine = response_line(200);

    std::map<std::string, std::string> extraHeaders = {{"Allow", "OPTIONS, GET"}};
    std::string responseHeaders = response_headers(extraHeaders);

    // Joining the response components
    std::vector<std::string> responseComponents = {responseLine, responseHeaders, blank_line};
    
    std::string out = responseLine + responseHeaders + blank_line;
    return out;
}

std::string HTTPServer::response_GET_handler(HTTPRequest &request)
{
    // remove all trailing and ending slashes from the requested path
    size_t start = 0;
    size_t end = request.m_uri.size();
    while (start < end && request.m_uri[start] == '/') {
        ++start;
    }
    while (end > start && request.m_uri[end - 1] == '/') {
        --end;
    }
    std::string path = request.m_uri.substr(start, end - start);

    // serve index.html if no path is requested
    if (!path.size())
        path = HOME_PAGE_PATH;

    std::string path_msg = "Requested Path: " + path + "\n";
    defaultLog(path_msg, true);

    std::string responseLine;
    std::string responseHeaders;
    std::string responseBody;

    // deleted: std::experimental::filesystem::exists(path) && !std::experimental::filesystem::is_directory(path)
    std::ifstream ifstr(path);
    if (ifstr.good()) {
        responseLine = response_line(200);
        defaultLog(responseLine, true);

        // Find out a file's MIME type (no default [TODO])
        std::string contentType = MimeTypes::getType(path.c_str());

        std::map<std::string, std::string> extraHeaders = {{"Content-Type", contentType}};
        responseHeaders = response_headers(extraHeaders);

        std::ifstream fileStream(path, std::ios::binary);
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        responseBody = buffer.str();
    } else {
        responseLine = response_line(404);
        defaultLog(responseLine, true);

        // send default 404 error html page
        std::map<std::string, std::string> extraHeaders = {{"Content-Type", "text/html"}};
        responseHeaders = response_headers(extraHeaders);

        // read from error/404.html
        std::ifstream fileStream("error/404.html", std::ios::binary);
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        responseBody = buffer.str();
    }

    std::vector<std::string> responseComponents = {responseLine, responseHeaders, blank_line, responseBody};
    std::string out = responseLine + responseHeaders + blank_line + responseBody;

    return out;
}

std::string HTTPServer::response_HTTP_501_handler(HTTPRequest &request)
{
    std::string responseLine = response_line(501);

    defaultLog(responseLine, true);

    std::map<std::string, std::string> map{};
    std::string responseHeaders = response_headers(map);

    std::string out = responseLine + responseHeaders + blank_line;
    return out;
}
