#include "pch.h"

#include "mammoth/string.h"

TEST(StringParserTest, IsInt32) {
    EXPECT_TRUE(StringParser::isInt32("234"));

    EXPECT_FALSE(StringParser::isInt32("asd"));
    EXPECT_TRUE(StringParser::isInt32("343"));
    EXPECT_FALSE(StringParser::isInt32("3423dfa3")); // TODO: this is a bug
}

TEST(StringParserTest, ParseInt32) {
    EXPECT_EQ(StringParser::parseInt32("343421"), 343421);
    EXPECT_EQ(StringParser::parseInt32("3423dfa3"), 3423); // TODO: this is a bug
}