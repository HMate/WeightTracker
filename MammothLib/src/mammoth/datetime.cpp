#include "datetime.h"

#include "logger.h"


TimeSpan::TimeSpan(int32 day, int32 hours, int32 minutes, int32 seconds, int32 mseconds)
{
    m_msecond = day * TimeSpan::DayInMicroSeconds + hours * TimeSpan::HourInMicroSeconds + minutes * TimeSpan::MinuteInMicroSeconds +
        seconds * TimeSpan::SecondInMicroSeconds + mseconds;
}

TimeSpan TimeSpan::Day(int32 count)
{
    return TimeSpan(count);
}


// TODO: implement format string if needed, should conform to http://www.cplusplus.com/reference/ctime/strftime/
DateTime::DateTime(const String& dateString/*, std::string format = "%F %T"*/)
{
    parseDate(dateString);
}

DateTime::DateTime(int32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds, int64 mseconds)
{
    setDateTime(year, month, day, hours, minutes, seconds, mseconds);
}

bool DateTime::isValid(const String& dateString)
{
    strarray dateTimeParts = dateString.split(" ");
    if(dateTimeParts.size() == 2)
    {
        strarray dateParts = String(dateTimeParts[0]).split("-");
        strarray timeParts = String(dateTimeParts[1]).split(":");
        if(dateParts.size() == 3 && timeParts.size() == 3)
        {
            if(StringParser::isInt32(dateParts[0]) && StringParser::isUInt32(dateParts[1]) && StringParser::isUInt32(dateParts[2]) &&
                StringParser::isUInt32(timeParts[0]) && StringParser::isUInt32(timeParts[1]) && StringParser::isUInt32(timeParts[2]))
            {
                bool year = StringParser::isInt32(dateParts[0]);
                bool month = StringParser::isUInt32(dateParts[1]);
                bool day = StringParser::isUInt32(dateParts[2]);

                bool hour = StringParser::isInt32(timeParts[0]);
                bool min = StringParser::isUInt32(timeParts[1]);
                bool sec = StringParser::isUInt32(timeParts[2]);
                return year && month && day && hour && min && sec;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void DateTime::parseDate(const String& dateString/*, std::string format = "%F %T"*/)
{
    // TODO: Need isValidDate method, to check if string is valid date
    strarray dateTimeParts = dateString.split(" ");
    if(dateTimeParts.size() == 2)
    {
        strarray dateParts = String(dateTimeParts[0]).split("-");
        strarray timeParts = String(dateTimeParts[1]).split(":");
        if(dateParts.size() == 3 && timeParts.size() == 3)
        {
            if(StringParser::isInt32(dateParts[0]) && StringParser::isUInt32(dateParts[1]) && StringParser::isUInt32(dateParts[2]) &&
                StringParser::isUInt32(timeParts[0]) && StringParser::isUInt32(timeParts[1]) && StringParser::isUInt32(timeParts[2]))
            {
                // TODO: How to give negative years
                int32 year = StringParser::parseInt32(dateParts[0]);
                uint32 month = StringParser::parseUInt32(dateParts[1]);
                uint32 day = StringParser::parseUInt32(dateParts[2]);

                int32 hour = StringParser::parseInt32(timeParts[0]);
                uint32 min = StringParser::parseUInt32(timeParts[1]);
                uint32 sec = StringParser::parseUInt32(timeParts[2]);
                setDateTime(year, month, day, hour, min, sec);
            }
            else
            {
                Log::log("Failed to parse in date: %s, non valid number in date or time.", dateString);
            }
        }
        else
        {
            Log::log("Failed to parse in date: %s, cant split date(-) or time(:) parts to 3.", dateString);
        }
    }
    else
    {
        Log::log("Failed to parse in date: %s, split on ' ' didnt produce 2 parts.", dateString);
    }
}

void DateTime::setDateTime(int32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds, int64 mseconds)
{
    int64 overflow = 0;
    m_msecond = mseconds % 1000000;
    overflow = mseconds / 1000000;
    m_second = (seconds + overflow) % 60;
    overflow = (seconds + overflow) / 60;
    m_minute = (minutes + overflow) % 60;
    overflow = (minutes + overflow) / 60;
    m_hour = (hours + overflow) % 24;
    overflow = (hours + overflow) / 24;

    // set initial year, month, add overflow to this if there is any based on initial date
    m_year = year;
    m_month = month;
    m_day = 0;

    uint32 daysToAdd = day + overflow;
    int32 daysInMonth = 0;
    do
    {
        m_year += ((m_month - 1) / 12);
        m_month = ((m_month - 1) % 12) + 1;

        overflow = 0;
        std::vector<int32> monthStart{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
        if(!isLeapYear())
        {
            monthStart = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
        }

        int32 nextMonthStart = monthStart[m_month];
        daysInMonth = nextMonthStart - monthStart[m_month - 1];

        if(daysToAdd >= daysInMonth)
        {
            daysToAdd = (daysToAdd - daysInMonth);
            m_month++;
        }
    } while(daysToAdd >= daysInMonth);

    m_year += ((m_month - 1) / 12);
    m_month = ((m_month - 1) % 12) + 1;
    m_day = daysToAdd;
}

bool DateTime::isLeapYear() const
{
    return (m_year % 4) == 0;
}

DateTime DateTime::operator+(const TimeSpan& dt) const
{
    return DateTime(m_year, m_month, m_day, m_hour, m_minute, m_second, m_msecond + dt.m_msecond);
}

std::string DateTime::toString(/*TODO: param as format*/) const
{
    return StringFormatter::format("%s-%s-%s %s:%s:%s", m_year, m_month, m_day, m_hour, m_minute, m_second);
}

int32 DateTime::getYear() const
{
    return m_year;
}

int32 DateTime::getMonth() const
{
    return m_month;
}

int32 DateTime::getDay() const
{
    return m_day;
}

int32 DateTime::getHour() const
{
    return m_hour;
}

int32 DateTime::getMinute() const
{
    return m_minute;
}

int32 DateTime::getSecond() const
{
    return m_second;
}

int32 DateTime::getMicrosecond() const
{
    return m_msecond;
}
