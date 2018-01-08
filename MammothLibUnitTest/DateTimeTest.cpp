#include "pch.h"

#include "mammoth/datetime.h"

void assertTestDate(const DateTime& dt, char* tostring, int32 year = -1, int32 month = -1, int32 day = -1, int32 hour = -1, int32 min = -1, int32 sec = -1, int32 msec = -1)
{
    EXPECT_EQ(dt.toString(), tostring);
    if(year >= 0)
        EXPECT_EQ(dt.getYear(), year);
    if(month >= 0)
        EXPECT_EQ(dt.getMonth(), month);
    if(day >= 0)
        EXPECT_EQ(dt.getDay(), day);
    if(hour >= 0)
        EXPECT_EQ(dt.getHour(), hour);
    if(min >= 0)
        EXPECT_EQ(dt.getMinute(), min);
    if(sec >= 0)
        EXPECT_EQ(dt.getSecond(), sec);
    if(msec >= 0)
        EXPECT_EQ(dt.getMicrosecond(), msec);
}

TEST(DateTimeTest, Getters) {
    assertTestDate(DateTime("2002-1-21 23:22:01"), "2002-1-21 23:22:1", 2002, 1, 21, 23, 22, 1, 0);
    assertTestDate(DateTime("2002-1-21 23:22:01"), "2002-1-21 23:22:1");
    assertTestDate(DateTime("1876-02-18 00:32:49"), "1876-2-18 0:32:49", 1876, 2, 18, 0, 32, 49, 0);
    assertTestDate(DateTime("1876-2-18 0:32:49"), "1876-2-18 0:32:49", 1876, 2, 18, 0, 32, 49, 0);
    assertTestDate(DateTime("0-1-1 0:0:0"), "0-1-1 0:0:0", 0, 1, 1, 0, 0, 0, 0);
}

TEST(DateTimeTest, Overflow){
    assertTestDate(DateTime(2002, 1, 21, 23, 22, 34, 1000023), "2002-1-21 23:22:35", 2002, 1, 21, 23, 22, 35, 23);
    assertTestDate(DateTime(2002, 1, 21, 23, 22, 34, 10997699), "2002-1-21 23:22:44", 2002, 1, 21, 23, 22, 44, 997699);
    assertTestDate(DateTime("2002-1-21 23:22:60"), "2002-1-21 23:23:0");
    assertTestDate(DateTime("2002-1-21 23:22:99"), "2002-1-21 23:23:39");
    assertTestDate(DateTime("2002-1-21 10:99:27"), "2002-1-21 11:39:27");
    assertTestDate(DateTime("2002-1-21 27:48:60"), "2002-1-22 3:49:0");
    assertTestDate(DateTime("2002-1-21 99:59:20"), "2002-1-25 3:59:20");
    assertTestDate(DateTime("2002-1-21 23:59:60"), "2002-1-22 0:0:0");
    assertTestDate(DateTime("2002-1-21 99:59:60"), "2002-1-25 4:0:0");
    assertTestDate(DateTime("2002-1-31 24:56:14"), "2002-2-1 0:56:14");
    assertTestDate(DateTime("2002-12-31 24:36:37"), "2003-1-1 0:36:37");
    assertTestDate(DateTime("2002-45-7 12:31:32"), "2005-9-7 12:31:32");
    assertTestDate(DateTime("2002-50-31 26:66:93"), "2006-3-4 3:7:33");
}

TEST(DateTimeTest, AddingTimespan){
    assertTestDate(DateTime("2002-1-21 23:22:01") + TimeSpan::Day(1), "2002-1-22 23:22:1");
}