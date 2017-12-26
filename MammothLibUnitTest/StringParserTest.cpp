#include "pch.h"

#include "mammoth/string.h"

TEST(StringParserTest, IsInt32) {
    EXPECT_TRUE(StringParser::isInt32("234"));

    EXPECT_FALSE(StringParser::isInt32("asd"));
    EXPECT_TRUE(StringParser::isInt32("343"));

    EXPECT_TRUE(StringParser::isInt32("2147483647")); // INT_MAX
    EXPECT_TRUE(StringParser::isInt32("-2147483648")); // INT_MIN
    EXPECT_FALSE(StringParser::isInt32("2147483648"));
    EXPECT_FALSE(StringParser::isInt32("-2147483649"));

    // TODO: these are bugs, this should be EXPECT_FALSE
    EXPECT_TRUE(StringParser::isInt32("3423dfa3"));
    EXPECT_TRUE(StringParser::isInt32("3423 3"));
}

TEST(StringParserTest, ParseInt32) {
    EXPECT_EQ(StringParser::parseInt32("343421"), 343421);
    EXPECT_EQ(StringParser::parseInt32("2147483647"), INT_MAX);
    EXPECT_EQ(StringParser::parseInt32("-2147483648"), INT_MIN);
    // TODO: this is a bug, but it may be okayish, as we dont exatly know what to parse for a bad string
    EXPECT_EQ(StringParser::parseInt32("3423dfa3"), 3423);
    EXPECT_TRUE(StringParser::isInt32("3423 3"), 3423);
}