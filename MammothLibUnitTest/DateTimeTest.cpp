#include "pch.h"

#include "mammoth/datetime.h"

void assertTestDate(const DateTime& dt, char* tostring, int32 year, int32 month, int32 day, int32 hour, int32 min, int32 sec, int32 msec)
{
    EXPECT_EQ(dt.toString(), tostring);
    EXPECT_EQ(dt.getYear(), year);
    EXPECT_EQ(dt.getMonth(), month);
    EXPECT_EQ(dt.getDay(), day);
    EXPECT_EQ(dt.getHour(), hour);
    EXPECT_EQ(dt.getMinute(), min);
    EXPECT_EQ(dt.getSecond(), sec);
    EXPECT_EQ(dt.getMicrosecond(), msec);
}

TEST(DateTimeTest, DateGetters) {
    assertTestDate(DateTime("2002-1-21 23:22:01"), "2002-1-21 23:22:1", 2002, 1, 21, 23, 22, 1, 0);
    assertTestDate(DateTime("1876-02-18 00:32:49"), "1876-2-18 0:32:49", 1876, 2, 18, 0, 32, 49, 0);
    assertTestDate(DateTime("1876-2-18 0:32:49"), "1876-2-18 0:32:49", 1876, 2, 18, 0, 32, 49, 0);
    assertTestDate(DateTime("0-1-1 0:0:0"), "0-1-1 0:0:0", 0, 1, 1, 0, 0, 0, 0);
}