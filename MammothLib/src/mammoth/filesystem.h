#pragma once
#include <fstream>
#include <iostream>
#include "types.h"

class File
{
    std::string m_contents;
    int64 m_pos;

public:
    File();
    ~File();

    // Load the contents of a file, and store them into this File object.
    void loadFile(const std::string& filePath);
    // Save the stored contents to a file on the given path
    void saveFile(const std::string& filePath);

    // Clear the contents of this file.
    void clear();
    std::string readLine();
    void writeLine(std::string line);
    bool isEndOfFile();

};

class FileSystem
{
public:
    static std::string getCurrentWorkingDirectory();
};

