#include "ConfigFile.h"

#include <fstream>
#include <iostream>


ConfigFile::ConfigFile(const string &filePath)
{
    string lineBuffer;
    string moduleBuffer;

    ifstream file(filePath);
    
    if (file.fail()) return;

    while (getline(file, lineBuffer)) {
        switch (lineBuffer.at(0)) {
            case ' ': case '\n': case '\r': break;
            case '[': moduleBuffer = GetModule(lineBuffer); break;
            default: AddLine(lineBuffer, moduleBuffer); break;
        }
    }
}

string ConfigFile::GetModule(const string &line)
{
    string module = "";

    for (const char lineChar : line) {
        switch (lineChar) {
            case '[': case '{': case '(': break;
            case ']': case '}': case ')': return module;
            case '\n': case '\r': return "";
            case ' ': module += '.';
            default: module += lineChar; break;
        }
    }

    return "";
}

void ConfigFile::AddLine(const string &line, const string &module)
{
    bool isKey = true;

    string value = "";
    string key = module + '.';

    for (const char lineChar : line) {
        switch (lineChar) {
            case ' ': case '\n': case '\r': break;
            case '=': isKey = false; break;
            default: (isKey) ? key += lineChar : value += lineChar; break;
        }
    }

    configContent[key] = value;
}

const string &ConfigFile::operator[]  (const string &key)
{
    return configContent[key];
}