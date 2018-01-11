#pragma once
#include <string>
#include <vector>
#include "types.h"

typedef std::vector<std::string> strarray;

class String
{
    std::string m_content;
public:
    String(const std::string& content = "") : m_content(content){}
    String(const char* content) : m_content(content){}

    strarray split(const std::string& tokens) const;
    operator std::string();
    const char* str();
};


template<typename T>
class FormatParam
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
std::string FormatParam<uint32>::toString() { return std::to_string(m_val); }
std::string FormatParam<int64>::toString() { return std::to_string(m_val); }
std::string FormatParam<uint64>::toString() { return std::to_string(m_val); }
std::string FormatParam<float>::toString() { return std::to_string(m_val); }
std::string FormatParam<double>::toString() { return std::to_string(m_val); }

class StringFormatter
{
public:
    static std::string format(const std::string& format)
    {
        std::string result(format);
        auto pos = result.find("%%s");
        while(pos != std::string::npos)
        {
            auto start = result.begin() + pos;
            result.replace(start, start+3, "%s");
            pos = result.find("%%s");
        }
        return result;
    }

    template<class T>
    static std::string _format(const std::string& format, FormatParam<T> p0)
    {
        auto pos = format.find("%s");
        if(pos == std::string::npos)
        {
            return StringFormatter::format(format);
        }

        while((pos > 0) && (format[pos-1] == '%'))
        {
            pos = format.find("%s", pos+1);
            if(pos == std::string::npos)
            {
                return StringFormatter::format(format);
            }
        }

        std::string result;
        result.append(format.substr(0, pos));
        result.append(p0.toString());
        result.append(format.substr(pos+2));
        
        return StringFormatter::format(result);
    }

    template<class U, class ...T>
    static std::string _format(const std::string& format, FormatParam<U> p0, T... pargs)
    {
        auto pos = format.find("%s");
        if(pos == std::string::npos)
        {
            return StringFormatter::format(format);
        }

        while((pos > 0) && (format[pos - 1] == '%'))
        {
            pos = format.find("%s", pos + 1);
            if(pos == std::string::npos)
            {
                return StringFormatter::format(format);
            }
        }

        std::string result;
        result.append(format.substr(0, pos));
        result.append(p0.toString());
        result.append(format.substr(pos+2));

        return StringFormatter::format<T...>(result, pargs...);
    }

    // Wrapper methods, so i dont have to explicitly write out template parameters when calling
    template<typename T>
    static std::string format(const std::string formatString, T p0) 
    {
        return _format<T>(formatString, p0);
    }

    template<typename ...T>
    static std::string format(const std::string& formatString, T... pargs)
    {
        return _format<T...>(formatString, pargs...);
        
    }
};

class StringParser
{
public:
    static bool isUInt32(std::string);
    static uint32 parseUInt32(std::string);

    static bool isInt32(std::string);
    static int32 parseInt32(std::string);

    static bool isFloat(std::string);
    static float parseFloat(std::string);
};