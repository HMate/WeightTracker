#include "common.h"
#include "string.h"

class DateTime
{
    int32 m_year;
    int32 m_month;
    int32 m_day;

    int32 m_hour;
    int32 m_minute;
    int32 m_second;

public:
    DateTime(String dateString/*, std::string format = "%F %T"*/);
    DateTime(int32 year, int32 month, int32 day, int32 hours, int32 minutes, int32 seconds);
};