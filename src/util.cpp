#include "util.h"
#include "defaults.h"

#include <fstream>
#include <iostream>

// silent only logs into DEFAULT_LOGGING_PATH and not cout
void defaultLog(std::string &content, bool silent)
{
    if (!silent) {
        std::cout << content;
        std::cout.flush();
    }
    appendStringToFile(DEFAULT_LOGGING_PATH, content.data());
}

void defaultLog(const char *content, bool silent)
{
    if (!silent) {
        std::cout << content;
        std::cout.flush();
    }
    appendStringToFile(DEFAULT_LOGGING_PATH, content);
}

bool appendStringToFile(const char *path, const char *content)
{
    std::ofstream file(path, std::ios::app);
    if (!file.is_open())
        return false;
    
    file << content;

    file.close();
    if (file.is_open())
        return false;
    return true;
}

bool removeFile(const char* path)
{
    if (!std::remove(path))
        return false;
    return true;      
}

std::stringstream &readFile(const char *path)
{
    std::ofstream file(path, std::ios::app);
    if (!file.is_open())
        return false;
}

bool parseFile(FileData &fdata)
{
    
    return false;
}
