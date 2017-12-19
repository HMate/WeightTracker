#pragma once

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include <string>
#include "string.h"


class Log
{
public:
    static void log(const std::string& msg)
    {
        std::string withNewLine(msg);
        withNewLine.append("\n");
#ifdef PLATFORM_WINDOWS
        OutputDebugString(withNewLine.c_str());
#endif
    }

    template<typename T>
    static void log(const std::string& msg, T p0)
    {
        std::string withNewLine(msg);
        withNewLine.append("\n");
#ifdef PLATFORM_WINDOWS
        auto res = StringFormatter::format<T>(withNewLine, p0);
        OutputDebugString(res.c_str());
#endif
    }

    template<typename ...T>
    static void log(const std::string& msg, T... pargs)
    {
        std::string withNewLine(msg);
        withNewLine.append("\n");
#ifdef PLATFORM_WINDOWS
        auto res = StringFormatter::format<T...>(withNewLine, pargs...);
        OutputDebugString(res.c_str());
#endif
    }
};
