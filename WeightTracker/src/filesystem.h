#include "common.h"
#include <fstream>
#include <iostream>


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
    void loadFile(std::string filePath);
    std::string readLine();
};

class FileSystem
{
public:
    static std::string getCurrentWorkingDirectory();
};

