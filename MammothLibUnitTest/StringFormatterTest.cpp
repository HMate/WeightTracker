#include "pch.h"

#include "mammoth/string.h"

TEST(StringFormatterTest, FormatUsage) {
    EXPECT_EQ(StringFormatter::format<const char*>("Hello %s", "mammoth"), "Hello mammoth");
}