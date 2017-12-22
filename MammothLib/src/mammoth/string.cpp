#include "string.h"

#include <limits>
#include "logger.h"

/**
Split the string to parts around the given token.
Gives back a list of strings. The list elemnts contain the substring without the token in original order.
*/
strarray String::split(const std::string& token)
{
    //from: https://www.reddit.com/r/cpp/comments/5dxnwm/why_doesnt_stdstring_have_a_split_function/daarp86/
    strarray results;
    size_t pos1 = 0, pos2 = 0;

    do
    {
        pos1 = m_content.find(token, pos2);
        if(pos1 == pos2) {
            pos2 += token.size(); 
            results.push_back(""); 
            continue;
        }
        if(pos1 == std::string::npos){
            results.push_back(m_content.substr(pos2)); 
            break;
        }
        results.push_back(m_content.substr(pos2, pos1 - pos2));
        pos2 = pos1 + token.size();
    } while(pos1 != std::string::npos);


    return results;
}

String::operator std::string()
{
    return m_content;
}

const char* String::str()
{
    return m_content.c_str();
}

// ----------------------------------------------------------------------------------------------
// TODO: I guess own functions would be better instead of using the std ones and catching exceptions
//  This method may be slow, but for know its fine.

bool StringParser::isInt32(std::string input)
{
    try
    {
        // TODO: this incorrectly parses in the string "3423dfa3" as 3423
        int32 val = std::stoi(input);
        return true;
    }
    catch(const std::exception&)
    {
        return false;
    }
}

int32 StringParser::parseInt32(std::string input)
{
    int32 val;
    try
    {
        val = std::stoi(input);
    }
    catch(const std::exception&)
    {
        Log::log("Cant parse in int32: %s", input);
    }
    return val;
}

bool StringParser::isUInt32(std::string input)
{
    try
    {
        int64 val = std::stoll(input);
        if(val < 0)
            return false;
        if(val > static_cast<int64>(UINT32_MAX))
            return false;
        return true;
    }
    catch(const std::exception&)
    {
        return false;
    }
}

uint32 StringParser::parseUInt32(std::string input)
{
    uint32 val;
    try
    {
        val = static_cast<uint32>(std::stoll(input));
    }
    catch(const std::exception&)
    {
        Log::log("Cant parse in uint32: %s", input);
    }
    return val;
}