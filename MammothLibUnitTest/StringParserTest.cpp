#include "pch.h"

#include "mammoth/string.h"

TEST(StringParserTest, IsInt32) {
    EXPECT_TRUE(StringParser::isInt32("234"));
}