#include "string.h"

#include <limits>
#include "logger.h"

/**
Split the string to parts around the given token.
Gives back a list of strings. The list elemnts contain the substring without the token in original order.
*/
strarray String::split(const std::string& token) const
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

bool StringParser::isIntNumber(std::string input)
{
    for(int i = 0; i < input.size(); i++)
    {
        const auto& c = input[i];
        if(c < '0' || c > '9')
        {
            if(i == 0 && c == '-')
                continue;
            return false;
        }
    }
    return input.size() > 0;
}

bool StringParser::isUIntNumber(std::string input)
{
    for(int i = 0; i < input.size(); i++)
    {
        const auto& c = input[i];
        if(c < '0' || c > '9')
        {
            return false;
        }
    }
    return input.size() > 0;
}

bool StringParser::isInt32(std::string input)
{
    // stoi parses numbers until first non-number character is met.
    // We dont want that, we want only strings with actual numbers, so check that
    if(!StringParser::isIntNumber(input))
        return false;
    try
    {
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
    int32 val = 0;
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
    if(!StringParser::isUIntNumber(input))
        return false;

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
    uint32 val = 0;
    try
    {
        // can over/underflow, but doesnt matter, user should check if its a valid string before
        val = static_cast<uint32>(std::stoll(input));
    }
    catch(const std::exception&)
    {
        Log::log("Cant parse in uint32: %s", input);
    }
    return val;
}

bool StringParser::isFloat(std::string input)
{
    try
    {
        float val = std::stof(input);
        if(val > static_cast<int64>(UINT32_MAX))
            return false;
        return true;
    }
    catch(const std::exception&)
    {
        return false;
    }
}

float StringParser::parseFloat(std::string input)
{
    float val = 0.0f;
    try
    {
        val = std::stof(input);
    }
    catch(const std::exception&)
    {
        Log::log("Cant parse in uint32: %s", input);
    }
    return val;
}