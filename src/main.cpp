#include "tcpserver.h"
#include "httpserver.h"
#include "util.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    FileData fd;
    parseFile(fd);
    
    HTTPServer server(argv[1], 80);
    server.startup();

    return 0;
}
