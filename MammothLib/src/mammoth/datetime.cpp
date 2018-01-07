#include "datetime.h"

#include "logger.h"

DateTime::DateTime(std::string dateString/*, std::string format = "%F %T"*/)
{
    parseDate(String(dateString));
}

// TODO: implement format string if needed, should conform to http://www.cplusplus.com/reference/ctime/strftime/
DateTime::DateTime(String dateString/*, std::string format = "%F %T"*/)
{
    parseDate(dateString);
}

void DateTime::parseDate(String dateString/*, std::string format = "%F %T"*/)
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

DateTime::DateTime(int32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds, uint32 mseconds)
{
    setDateTime(year, month, day, hours, minutes, seconds, mseconds);
}

void DateTime::setDateTime(int32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds, uint32 mseconds)
{
    m_year = year;
    m_month = month;
    m_day = day;
    m_hour = hours;
    m_minute = minutes;
    m_second = seconds;
    m_msecond = mseconds;
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
