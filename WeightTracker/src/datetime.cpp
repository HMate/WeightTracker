#include "datetime.h"



// TODO: mplement format string if needed, should conform to http://www.cplusplus.com/reference/ctime/strftime/
DateTime::DateTime(String dateString/*, std::string format = "%F %T"*/)
{
    strarray dateTimeParts = dateString.split(" ");
    if(dateTimeParts.size() == 6)
    {

    }
    else
    {
        
    }
}

DateTime::DateTime(int32 year, int32 month, int32 day, int32 hours, int32 minutes, int32 seconds) :
    m_year(year), m_month(month), m_day(day), m_hour(hours), m_minute(minutes), m_second(seconds)
{}