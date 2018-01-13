#include "pch.h"

#include "mammoth/string.h"

TEST(StringParserTest, IsIntNumber) {
    EXPECT_TRUE(StringParser::isIntNumber("234"));
    EXPECT_TRUE(StringParser::isIntNumber("343"));

    EXPECT_TRUE(StringParser::isIntNumber("2147483647")); // INT_MAX
    EXPECT_TRUE(StringParser::isIntNumber("-2147483648")); // INT_MIN
    EXPECT_TRUE(StringParser::isIntNumber("2147483648"));
    EXPECT_TRUE(StringParser::isIntNumber("-2147483649"));
    EXPECT_TRUE(StringParser::isIntNumber("21474836472147483647214748364721474836472147483647"));
    EXPECT_TRUE(StringParser::isIntNumber("-21474836472147483647214748364721474836472147483647"));
    EXPECT_TRUE(StringParser::isIntNumber("927598716587615618751577126487326536578264247"));

    EXPECT_FALSE(StringParser::isIntNumber("4612-767"));
    EXPECT_FALSE(StringParser::isIntNumber("+4612767"));
    EXPECT_FALSE(StringParser::isIntNumber("--4612767"));
    EXPECT_FALSE(StringParser::isIntNumber("-4612-767"));
    EXPECT_FALSE(StringParser::isIntNumber("4612767198659126571a"));
    EXPECT_FALSE(StringParser::isIntNumber("4612,71"));
    EXPECT_FALSE(StringParser::isIntNumber("4612.71"));
    EXPECT_FALSE(StringParser::isIntNumber("4612.0"));
    EXPECT_FALSE(StringParser::isIntNumber("461."));
    EXPECT_FALSE(StringParser::isIntNumber("asd"));
    EXPECT_FALSE(StringParser::isIntNumber("3423dfa3"));
    EXPECT_FALSE(StringParser::isIntNumber("3423 3"));
    EXPECT_FALSE(StringParser::isIntNumber(""));
    EXPECT_FALSE(StringParser::isIntNumber(" "));
    EXPECT_FALSE(StringParser::isIntNumber("                        "));
    EXPECT_FALSE(StringParser::isIntNumber("  3  "));
    EXPECT_FALSE(StringParser::isIntNumber("   3d "));
    EXPECT_FALSE(StringParser::isIntNumber("0x3"));
    EXPECT_FALSE(StringParser::isIntNumber("0x13d"));
}

TEST(StringParserTest, IsUIntNumber) {
    EXPECT_TRUE(StringParser::isUIntNumber("234"));
    EXPECT_TRUE(StringParser::isUIntNumber("343"));

    EXPECT_TRUE(StringParser::isUIntNumber("2147483647")); // INT_MAX
    EXPECT_TRUE(StringParser::isUIntNumber("2147483648"));
    EXPECT_TRUE(StringParser::isUIntNumber("21474836472147483647214748364721474836472147483647"));
    EXPECT_TRUE(StringParser::isUIntNumber("927598716587615618751577126487326536578264247"));

    EXPECT_FALSE(StringParser::isUIntNumber("4612767198659126571a"));
    EXPECT_FALSE(StringParser::isUIntNumber("-2147483648"));
    EXPECT_FALSE(StringParser::isUIntNumber("-2147483649"));
    EXPECT_FALSE(StringParser::isUIntNumber("-21474836472147483647214748364721474836472147483647"));
    EXPECT_FALSE(StringParser::isUIntNumber("asd"));
    EXPECT_FALSE(StringParser::isUIntNumber("3423dfa3"));
    EXPECT_FALSE(StringParser::isUIntNumber("3423 3"));
    EXPECT_FALSE(StringParser::isUIntNumber(""));
    EXPECT_FALSE(StringParser::isUIntNumber(" "));
    EXPECT_FALSE(StringParser::isUIntNumber("    "));
    EXPECT_FALSE(StringParser::isUIntNumber("  3  "));
    EXPECT_FALSE(StringParser::isUIntNumber("   3d "));
    EXPECT_FALSE(StringParser::isUIntNumber("0x3"));
    EXPECT_FALSE(StringParser::isUIntNumber("0x13d"));
}

TEST(StringParserTest, IsFloatNumber) {
    EXPECT_TRUE(StringParser::isFloatNumber("234"));
    EXPECT_TRUE(StringParser::isFloatNumber("343"));
    EXPECT_TRUE(StringParser::isFloatNumber("0.0"));
    EXPECT_TRUE(StringParser::isFloatNumber("1021.467"));
    EXPECT_TRUE(StringParser::isFloatNumber("1021.569876"));
    EXPECT_TRUE(StringParser::isFloatNumber("1021.560"));
    EXPECT_TRUE(StringParser::isFloatNumber("-231.0"));
    EXPECT_TRUE(StringParser::isFloatNumber(".130"));
    EXPECT_TRUE(StringParser::isFloatNumber("-.130"));

    EXPECT_TRUE(StringParser::isFloatNumber("2147483647")); // INT_MAX
    EXPECT_TRUE(StringParser::isFloatNumber("2147483648"));
    EXPECT_TRUE(StringParser::isFloatNumber("21474836472147483647214748364721474836472147483647"));
    EXPECT_TRUE(StringParser::isFloatNumber("927598716587615618751577126487326536578264247"));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483649"));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483649."));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483649.0"));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483649.000001"));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483649.3523525252187"));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483647214748364721474.8364721474836472147483647"));
    EXPECT_TRUE(StringParser::isFloatNumber("-214748364721474836472147434578965896518565647101.0"));
    EXPECT_TRUE(StringParser::isFloatNumber("-2147483647214748364721474.8364721474836472147483647"));

    EXPECT_FALSE(StringParser::isFloatNumber("3423dfa3"));
    EXPECT_FALSE(StringParser::isFloatNumber("3423 3"));
    EXPECT_FALSE(StringParser::isFloatNumber("3423_3"));
    EXPECT_FALSE(StringParser::isFloatNumber("879_0"));
    EXPECT_FALSE(StringParser::isFloatNumber("879e0"));
    EXPECT_FALSE(StringParser::isFloatNumber("3423..3"));
    EXPECT_FALSE(StringParser::isFloatNumber("--4612767"));
    EXPECT_FALSE(StringParser::isFloatNumber("-4612-767"));
    EXPECT_FALSE(StringParser::isFloatNumber("-4612.-767"));
    EXPECT_FALSE(StringParser::isFloatNumber("4612767198659126571a"));
    EXPECT_FALSE(StringParser::isFloatNumber("asd"));
    EXPECT_FALSE(StringParser::isFloatNumber(""));
    EXPECT_FALSE(StringParser::isFloatNumber(" "));
    EXPECT_FALSE(StringParser::isFloatNumber("    "));
    EXPECT_FALSE(StringParser::isFloatNumber("  3  "));
    EXPECT_FALSE(StringParser::isFloatNumber("   3d "));
    EXPECT_FALSE(StringParser::isFloatNumber("0x3"));
    EXPECT_FALSE(StringParser::isFloatNumber("0x13d"));
}

TEST(StringParserTest, IsInt32) {
    EXPECT_TRUE(StringParser::isInt32("234"));
    EXPECT_TRUE(StringParser::isInt32("-343"));
    EXPECT_FALSE(StringParser::isInt32("asd"));

    EXPECT_TRUE(StringParser::isInt32("2147483647")); // INT_MAX
    EXPECT_TRUE(StringParser::isInt32("-2147483648")); // INT_MIN
    EXPECT_FALSE(StringParser::isInt32("2147483648"));
    EXPECT_FALSE(StringParser::isInt32("-2147483649"));

    EXPECT_FALSE(StringParser::isInt32("3423dfa3"));
    EXPECT_FALSE(StringParser::isInt32("3423 3"));
}

TEST(StringParserTest, ParseInt32) {
    EXPECT_EQ(StringParser::parseInt32("343421"), 343421);
    EXPECT_EQ(StringParser::parseInt32("2147483647"), INT_MAX);
    EXPECT_EQ(StringParser::parseInt32("-2147483648"), INT_MIN);
    EXPECT_EQ(StringParser::parseInt32("2147483648"), 0);
    EXPECT_EQ(StringParser::parseInt32("-2147483649"), 0);
    // For now we dont care what it parses when the string is not a valid int32
    EXPECT_EQ(StringParser::parseInt32("3423dfa3"), 3423);
}

TEST(StringParserTest, IsUInt32) {
    EXPECT_TRUE(StringParser::isUInt32("234"));

    EXPECT_FALSE(StringParser::isUInt32("asd"));
    EXPECT_TRUE(StringParser::isUInt32("343"));
    EXPECT_TRUE(StringParser::isUInt32("2147483648"));

    EXPECT_TRUE(StringParser::isUInt32("4294967295")); // UINT_MAX
    EXPECT_FALSE(StringParser::isUInt32("4294967296")); // UINT_MAX

    EXPECT_FALSE(StringParser::isUInt32("3423dfa3"));
    EXPECT_FALSE(StringParser::isUInt32("3423 3"));
}

TEST(StringParserTest, ParseUInt32) {
    EXPECT_EQ(StringParser::parseUInt32("343421"), 343421);
    EXPECT_EQ(StringParser::parseUInt32("4294967295"), UINT_MAX);
    EXPECT_EQ(StringParser::parseUInt32("2147483648"), 2147483648);
    // For now we dont care what it parses when the string is not a valid uint32
    EXPECT_EQ(StringParser::parseUInt32("3423dfa3"), 3423);
}

TEST(StringParserTest, IsFloat) {
    EXPECT_TRUE(StringParser::isFloat("234"));
    EXPECT_TRUE(StringParser::isFloat("0.0"));
    EXPECT_TRUE(StringParser::isFloat("-1052.0"));
    EXPECT_TRUE(StringParser::isFloat("-89152.023421"));
    EXPECT_TRUE(StringParser::isFloat("3.43"));
    EXPECT_TRUE(StringParser::isFloat(".130"));
    EXPECT_TRUE(StringParser::isFloat("-.130"));

    EXPECT_FALSE(StringParser::isFloat("asd"));
    EXPECT_TRUE(StringParser::isFloat("343"));

    EXPECT_TRUE(StringParser::isFloat("2147483647"));
    EXPECT_TRUE(StringParser::isFloat("-2147483648"));
    EXPECT_TRUE(StringParser::isFloat("-2147483665387453465745835634867261872.343468276478126481764"));

    EXPECT_FALSE(StringParser::isFloat("3423dfa3"));
    EXPECT_FALSE(StringParser::isFloat("3423 3"));
    EXPECT_FALSE(StringParser::isFloat("3423_3"));
    EXPECT_FALSE(StringParser::isFloat("879_0"));
    EXPECT_FALSE(StringParser::isFloat("879e0"));
    EXPECT_FALSE(StringParser::isFloat("3423..3"));
}

TEST(StringParserTest, ParseFloat) {
    EXPECT_EQ(StringParser::parseFloat("343421"), 343421.f);
    EXPECT_EQ(StringParser::parseFloat("0.0"), 0.0f);
    EXPECT_EQ(StringParser::parseFloat("343.421"), 343.421f);
    EXPECT_EQ(StringParser::parseFloat("-130.0021"), -130.0021f);
    EXPECT_EQ(StringParser::parseFloat("2147483647"), (float)INT_MAX);
    EXPECT_EQ(StringParser::parseFloat("-2147483648"), (float)INT_MIN);
    EXPECT_EQ(StringParser::parseFloat("-.130"), -0.13f);
    EXPECT_EQ(StringParser::parseFloat("-2147483665387453465745835634867261872.343468276478126481764"), -2147483665387453465745835634867261872.343468276478126481764f);
    // For now we dont care what it parses when the string is not a valid float
    EXPECT_EQ(StringParser::parseFloat("3423.dfa3"), 3423.0f);
    EXPECT_EQ(StringParser::parseFloat("189.23..3"), 189.23f);
}