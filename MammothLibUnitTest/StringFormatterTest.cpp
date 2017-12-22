#include "pch.h"

#include "mammoth/string.h"

TEST(StringFormatterTest, FormatUsage) {
    EXPECT_EQ(StringFormatter::format<const char*>("Hello %s", "mammoth"), "Hello mammoth");
    EXPECT_EQ(StringFormatter::format("Hello"), "Hello");
    EXPECT_EQ(StringFormatter::format("Hello %s", "mammoth"), "Hello mammoth");
    EXPECT_EQ(StringFormatter::format("Hello %s %s", "mammoth"), "Hello mammoth %s");
    EXPECT_EQ(StringFormatter::format("Hello %s"), "Hello %s");
}