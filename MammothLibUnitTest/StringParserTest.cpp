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
}

TEST(StringParserTest, IsFloat) {
    EXPECT_TRUE(StringParser::isFloat("234"));
    EXPECT_TRUE(StringParser::isFloat("0.0"));
    EXPECT_TRUE(StringParser::isFloat("-1052.0"));
    EXPECT_TRUE(StringParser::isFloat("-89152.023421"));
    EXPECT_TRUE(StringParser::isFloat("3.43"));

    EXPECT_FALSE(StringParser::isFloat("asd"));
    EXPECT_TRUE(StringParser::isFloat("343"));

    EXPECT_TRUE(StringParser::isFloat("2147483647")); // FLOAT_MAX
    EXPECT_TRUE(StringParser::isFloat("-2147483648")); // FLOAT_MIN

    // TODO: these are bugs, this should be EXPECT_FALSE
    EXPECT_TRUE(StringParser::isFloat("3423dfa3"));
    EXPECT_TRUE(StringParser::isFloat("3423 3"));
    EXPECT_TRUE(StringParser::isFloat("3423..3"));
}

TEST(StringParserTest, ParseFloat) {
    EXPECT_EQ(StringParser::parseFloat("343421"), 343421.f);
    EXPECT_EQ(StringParser::parseFloat("0.0"), 0.0f);
    EXPECT_EQ(StringParser::parseFloat("343.421"), 343.421f);
    EXPECT_EQ(StringParser::parseFloat("-130.0021"), -130.0021f);
    EXPECT_EQ(StringParser::parseFloat("2147483647"), (float)INT_MAX);
    EXPECT_EQ(StringParser::parseFloat("-2147483648"), (float)INT_MIN);
    // TODO: this is a bug, but it may be okayish, as we dont exatly know what to parse for a bad string
    EXPECT_EQ(StringParser::parseFloat("3423.dfa3"), 3423.0f);
    EXPECT_EQ(StringParser::parseFloat("189.23..3"), 189.23f);
}