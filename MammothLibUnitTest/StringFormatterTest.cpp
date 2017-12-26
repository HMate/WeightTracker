#include "pch.h"

#include "mammoth/string.h"

TEST(StringFormatterTest, FormatUsage) {
    EXPECT_EQ(StringFormatter::format<const char*>("Hello %s!", "mammoth"), "Hello mammoth!");
    EXPECT_EQ(StringFormatter::format<const char*>("Hello %s", "mammoth"), "Hello mammoth");
    EXPECT_EQ(StringFormatter::format("%s"), "%s");
    EXPECT_EQ(StringFormatter::format("%s", 456213132313131), "456213132313131");
    EXPECT_EQ(StringFormatter::format("Hello"), "Hello");
    EXPECT_EQ(StringFormatter::format("Hello %s", "mammoth"), "Hello mammoth");
    EXPECT_EQ(StringFormatter::format("Hello %s", 345), "Hello 345");
    EXPECT_EQ(StringFormatter::format("Hello %s", 99.99f), "Hello 99.989998"); // TODO: more formatting options
    EXPECT_EQ(StringFormatter::format("Hello %s, %s roaming %s", 99.99f, "rambo", 847), "Hello 99.989998, rambo roaming 847");

    EXPECT_EQ(StringFormatter::format("Hello %s %s", "mammoth"), "Hello mammoth %s");
    EXPECT_EQ(StringFormatter::format("Hello %s"), "Hello %s");

    EXPECT_EQ(StringFormatter::format("Hello %s", "lucky", "star"), "Hello lucky");
    EXPECT_EQ(StringFormatter::format("Hello %s", 23, "star"), "Hello 23");

    EXPECT_EQ(StringFormatter::format("%%s"), "%s");
    EXPECT_EQ(StringFormatter::format("%%s", "stem"), "%s");
    EXPECT_EQ(StringFormatter::format("Hello %%s"), "Hello %s");
    EXPECT_EQ(StringFormatter::format("Hello %%s", "medium", "rare"), "Hello %s");
    EXPECT_EQ(StringFormatter::format("Hello %%s %%s%%s%%s %s", "lucky"), "Hello %s %s%s%s lucky");
    EXPECT_EQ(StringFormatter::format("Hello %%s %%s%s%%s %%s", "lucky", "star", 33), "Hello %s %slucky%s %s");
    EXPECT_EQ(StringFormatter::format("Hello %%s", "s", "oy"), "Hello %s");
}