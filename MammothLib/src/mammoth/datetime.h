#pragma once
#include "types.h"
#include "string.h"

class DateTime
{
    // TODO: pack these into single number if necessary
    int32 m_year;
    uint32 m_month;
    uint32 m_day;

    uint32 m_hour;
    uint32 m_minute;
    uint32 m_second;
    uint32 m_msecond;

public:
    DateTime(String dateString/*, std::string format = "%F %T"*/);
    DateTime(int32 year = 0, uint32 month = 1, uint32 day = 1, uint32 hours = 0, uint32 minutes = 0, uint32 seconds = 0, uint32 mseconds = 0);
    void setDateTime(int32 year = 0, uint32 month = 1, uint32 day = 1, uint32 hours = 0, uint32 minutes = 0, uint32 seconds = 0, uint32 mseconds = 0);
    std::string toString(/*TODO: param as format*/);
};
