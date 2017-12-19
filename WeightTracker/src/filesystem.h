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
    std::string m_filePath;
    std::fstream m_file;
    bool m_isOpen = false;

public:
    File(std::string filePath);
    ~File();
    std::string readFile();
};

class FileSystem
{
public:
    static std::string getCurrentWorkingDirectory();
    static File openFile(std::string filePath);
};

