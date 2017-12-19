#pragma once
#include <fstream>
#include <iostream>
#include "common.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef PLATFORM_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class File
{
    std::string m_contents;
    int64 m_pos;

public:
    File();
    ~File();
    void loadFile(const std::string& filePath);
    std::string readLine();
    bool isEndOfFile();
};

class FileSystem
{
public:
    static std::string getCurrentWorkingDirectory();
};

