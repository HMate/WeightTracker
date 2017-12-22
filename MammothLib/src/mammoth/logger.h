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
        OutputDebugStringA(withNewLine.c_str());
#endif
    }

    template<typename T>
    static void log(const std::string& msg, T p0)
    {
        std::string withNewLine(msg);
        withNewLine.append("\n");
#ifdef PLATFORM_WINDOWS
        auto res = StringFormatter::format(withNewLine, p0);
        OutputDebugStringA(res.c_str());
#endif
    }

    template<typename ...T>
    static void log(const std::string& msg, T... pargs)
    {
        std::string withNewLine(msg);
        withNewLine.append("\n");
#ifdef PLATFORM_WINDOWS
        auto res = StringFormatter::format(withNewLine, pargs...);
        OutputDebugStringA(res.c_str());
#endif
    }
};
