#pragma once
#include <string>
#include <vector>
#include "types.h"

typedef std::vector<std::string> strarray;

class COMMON_API String
{
    std::string m_content;
public:
    String(const std::string& content = "") : m_content(content){}

    strarray split(const std::string& tokens);
    operator std::string();
    const char* str();
};


template<typename T>
class COMMON_API FormatParam
{
    T m_val;
public:
    FormatParam(const T& v) : m_val(v){}
    std::string toString() 
    {
        return static_cast<std::string>(m_val);
    }
};

std::string FormatParam<int16>::toString() { return std::to_string(m_val); }
std::string FormatParam<int32>::toString() { return std::to_string(m_val); }
std::string FormatParam<int64>::toString() { return std::to_string(m_val); }
std::string FormatParam<float>::toString() { return std::to_string(m_val); }
std::string FormatParam<double>::toString() { return std::to_string(m_val); }

class COMMON_API StringFormatter
{
public:
    static std::string format(const std::string& format)
    {
        return format;
    }

    template<class T>
    static std::string format(const std::string& format, FormatParam<T> p0)
    {
        if(format.find("%s") < 0)
        {
            return format;
        }
        std::string result;
        strarray parts = String(format).split("%s");
        for(size_t i = 0; i<parts.size(); i++)
        {
            result.append(parts[i]);
            if(i == 0)
            {
                result.append(p0.toString());
            }
        }
        return result;
    }

    template<class U, class ...T>
    static std::string format(const std::string& format, FormatParam<U> p0, T... pargs)
    {
        if(format.find("%s") < 0)
        {
            return format;
        }
        std::string result;
        strarray parts = String(format).split("%s");
        for(size_t i = 0; i<parts.size() - 1; i++)
        {
            result.append(parts[i]);
            if(i == 0)
            {
                result.append(p0.toString());
            }
            else
            {
                result.append("%s");
            }
        }
        return StringFormatter::format<T...>(result, pargs...);
    }
};

class COMMON_API StringParser
{
public:
    static bool isUInt32(std::string);
    static uint32 parseUInt32(std::string);

    static bool isInt32(std::string);
    static int32 parseInt32(std::string);
};