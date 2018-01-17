#include "filesystem.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef PLATFORM_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iterator>

File::File() : m_contents("")
{
}

File::~File()
{
}

void File::loadFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    m_pos = 0;
    m_contents = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
}

void File::saveFile(const std::string& filePath)
{
    std::ofstream file(filePath, std::ofstream::out | std::ofstream::trunc);
    std::ostreambuf_iterator<char> it(file);
    std::copy(m_contents.begin(), m_contents.end(), it);
    file.close();
}

void File::clear()
{
    m_pos = 0;
    m_contents.clear();
}

std::string File::readLine()
{
    std::string line;
    if(m_pos < m_contents.size())
    {
       int64 nlpos = m_contents.find('\n', static_cast<uint32>(m_pos));
       if(nlpos != std::string::npos)
       {
           line = m_contents.substr(static_cast<uint32>(m_pos), static_cast<uint32>(nlpos-m_pos));
       }
       else
       {
           line = m_contents.substr(static_cast<uint32>(m_pos));
       }
       m_pos = nlpos + 1;
    }
    return line;
}

void File::writeLine(std::string line)
{
    m_contents += line + "\n";
}

bool File::isEndOfFile()
{
    return m_pos >= m_contents.size();
}

std::string FileSystem::getCurrentWorkingDirectory()
{
    char cCurrentPath[FILENAME_MAX];

    if(!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return "";
    }
    return cCurrentPath;
}