#include <gtest/gtest.h>

// Test case for equality checks
TEST(EqualityTests, OneEqualsOne)
{
    EXPECT_EQ(1, 1); // This should pass
}

TEST(EqualityTests, OneEqualsZero)
{
    EXPECT_EQ(1, 0); // This should fail
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}