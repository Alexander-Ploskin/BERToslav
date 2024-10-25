#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Function declarations (assuming these are defined elsewhere)
vector<pair<string, string>> parseMessages(const string& filename);

void createCSVFile(const string& filename, const vector<string>& lines) {
    ofstream file(filename);
    for (const auto& line : lines) {
        file << line << "\n";
    }
}

TEST(ParseMessagesTest, EmptyCSV) {
    createCSVFile("empty.csv", {"from,text"});
    vector<pair<string, string>> expected = {};
    vector<pair<string, string>> result = parseMessages("empty.csv");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, NoMessages) {
    createCSVFile("no_messages.csv", {"from,text"});
    vector<pair<string, string>> expected = {};
    vector<pair<string, string>> result = parseMessages("no_messages.csv");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, OnlyServiceMessages) {
    createCSVFile("only_service_messages.csv", {"from,text", "ServiceBot,"});
    vector<pair<string, string>> expected = {};
    vector<pair<string, string>> result = parseMessages("only_service_messages.csv");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, MixedMessageTypes) {
    createCSVFile("mixed_messages.csv", {"from,text", "Alice,\"What is the answer to the ultimate question of life, the Universe, and everything?\"", "ServiceBot,"});
    vector<pair<string, string>> expected = {{"Alice", "What is the answer to the ultimate question of life, the Universe, and everything?"}};
    vector<pair<string, string>> result = parseMessages("mixed_messages.csv");
    EXPECT_EQ(result, expected);
}

TEST(ParseMessagesTest, MultipleTextMessages) {
    createCSVFile("multiple_text_messages.csv", {"from,text", "Alice,\"What is the answer to the ultimate question of life, the Universe, and everything?\"", "Bob,\"42\""});
    vector<pair<string, string>> expected = {
        {"Alice", "What is the answer to the ultimate question of life, the Universe, and everything?"},
        {"Bob", "42"}
    };
    vector<pair<string, string>> result = parseMessages("multiple_text_messages.csv");
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
