#pragma once
#include "types.h"
#include "string.h"

class DateTime
{
    // TODO: pack these into single number if necessary
    int32 m_year; // from -14 billion (10^9) to 100 trillion (10^14) -> 2^27 + 2^42 -> 64 bits || -10k to +10k -> 14 bits
    uint32 m_month; // 12 -> 4 bits            || 4 b
    uint32 m_day; // 31 -> 5 bits              || 9 b

    uint32 m_hour; // 24 -> 5 bits             || 14 b
    uint32 m_minute; // 60 -> 6 bits           || 20 b
    uint32 m_second; // 6 bits                 || 26 bits
    uint32 m_msecond; // 1000000 -> 20 bits    || 46 bits + 14 = 60 -> 4 spare bits to years

    // year             |mon|day |hour|minut|secon|microsecond
    // 1234567890123456789012345678901234567890123456789012345678901234
    uint64 m_packed; 
public:
    DateTime(std::string dateString/*, std::string format = "%F %T"*/);
    DateTime(String dateString/*, std::string format = "%F %T"*/);
    DateTime(int32 year = 0, uint32 month = 1, uint32 day = 1, uint32 hours = 0, uint32 minutes = 0, uint32 seconds = 0, uint32 mseconds = 0);

    void parseDate(String dateString/*, std::string format = "%F %T"*/);

    void setDateTime(int32 year = 0, uint32 month = 1, uint32 day = 1, uint32 hours = 0, uint32 minutes = 0, uint32 seconds = 0, uint32 mseconds = 0);
    std::string toString(/*TODO: param as format*/) const;
    int32 getYear() const;
    int32 getMonth() const;
    int32 getDay() const;
    int32 getHour() const;
    int32 getMinute() const;
    int32 getSecond() const;
    int32 getMicrosecond() const;
};
