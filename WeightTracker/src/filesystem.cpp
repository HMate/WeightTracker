#include "filesystem.h"


#include <iterator>

File::File() : m_contents("")
{
}

File::~File()
{
}

void File::loadFile(const std::string& filePath)
{
    std::fstream file(filePath);
    m_pos = 0;
    m_contents = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
}

std::string File::readLine()
{
    std::string line;
    if(m_pos < m_contents.size())
    {
       int64 nlpos = m_contents.find('\n', static_cast<uint32>(m_pos));
       if(nlpos > -1)
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