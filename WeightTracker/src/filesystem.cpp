#include "filesystem.h"


#include <iterator>

File::File(std::string filePath) : m_filePath(filePath)
{
    m_file = std::fstream(m_filePath);
    m_isOpen = true;
}

File::~File()
{
    if(m_isOpen)
    {
        m_file.close();
    }
}

std::string File::readFile()
{
    std::string content((std::istreambuf_iterator<char>(m_file)), std::istreambuf_iterator<char>());
    return content;
}

std::string getCurrentWorkingDirectory()
{
    char cCurrentPath[FILENAME_MAX];

    if(!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return "";
    }
    return cCurrentPath;
}