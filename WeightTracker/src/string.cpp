#include "string.h"

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
