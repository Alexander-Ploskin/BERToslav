#include <gtest/gtest.h>

TEST(ParseMessagesTest, EmptyJSON) {
    vector<pair<string, string>> expected = {};
    vector<pair<string, string>> result = parseMessages("empty.json");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, NoMessages) {
    vector<pair<string, string>> expected = {};
    vector<pair<string, string>> result = parseMessages("no_messages.json");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, OnlyServiceMessages) {
    vector<pair<string, string>> expected = {};
    vector<pair<string, string>> result = parseMessages("only_service_messages.json");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, MixedMessageTypes) {
    vector<pair<string, string>> expected = {{"Alice", "What is the answer to the ultimate question of life, the Universe, and everything?"}};
    vector<pair<string, string>> result = parseMessages("mixed_messages.json");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, MultipleTextMessages) {
    vector<pair<string, string>> expected = {
        {"Alice", "What is the answer to the ultimate question of life, the Universe, and everything?"},
        {"Bob", "42"}
    };
    vector<pair<string, string>> result = parseMessages("multiple_text_messages.json");
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
