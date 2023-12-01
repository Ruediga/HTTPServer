#pragma once

#include <string>
#include <sstream>

void defaultLog(std::string &content, bool silent = false);
void defaultLog(const char *content, bool silent = false);

// file io
bool appendStringToFile(const char *path, const char *content);
bool removeFile(const char* path);
std::stringstream &readFile(const char* path);

// config file
typedef struct {
    std::string hostIP;
    int port;
} FileData;
// if fails abort
bool parseFile(FileData &fdata);