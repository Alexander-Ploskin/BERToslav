#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <regex>
#include <filesystem> // Include for filesystem operations
#include <cstdlib>    // for getenv

// Include the function to be tested
void postprocess();

class ProcessTopScoresTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create a temporary input file for each test
        std::ofstream inFile("test_input.txt");
        inFile << "id1 100\n";
        inFile << "id2 200\n";
        inFile << "id3 150\n";
        inFile << "id4 300\n";
        inFile << "id5 250\n";
        inFile << "id6 50\n";
        inFile.close();

        setenv("INPUT_FILENAME", "test_input.txt", 1);
        setenv("OUTPUT_FILENAME", "test_output.txt", 1);
    }

    void TearDown() override
    {
        // Remove temporary files after each test
        std::remove("test_input.txt");
        for (const auto &file : filesToRemove)
        {
            std::remove(file.c_str());
        }
    }

    std::vector<std::string> filesToRemove;
};

TEST_F(ProcessTopScoresTest, CorrectTopFiveIds)
{
    postprocess();

    // Find the created output file
    std::string outputFile = "test_output.txt";

    ASSERT_FALSE(outputFile.empty()) << "Output file not found";

    std::ifstream outFile(outputFile);
    std::vector<std::string> ids;
    std::string id;
    while (std::getline(outFile, id))
    {
        ids.push_back(id);
    }

    ASSERT_EQ(ids.size(), 5) << "Expected 5 IDs in the output file";
    EXPECT_EQ(ids[0], "id4");
    EXPECT_EQ(ids[1], "id5");
    EXPECT_EQ(ids[2], "id2");
    EXPECT_EQ(ids[3], "id3");
    EXPECT_EQ(ids[4], "id1");
}

TEST_F(ProcessTopScoresTest, LessThanFiveEntries)
{
    std::ofstream inFile("test_input_small.txt");
    inFile << "id1 100\n";
    inFile << "id2 200\n";
    inFile << "id3 150\n";
    inFile.close();

    setenv("INPUT_FILENAME", "test_input_small.txt", 1);

    postprocess();

    // Find the created output file
    std::string outputFile = "test_output.txt";

    ASSERT_FALSE(outputFile.empty()) << "Output file not found";

    std::ifstream outFile(outputFile);
    std::vector<std::string> ids;
    std::string id;
    while (std::getline(outFile, id))
    {
        ids.push_back(id);
    }

    ASSERT_EQ(ids.size(), 3) << "Expected 3 IDs in the output file";
    EXPECT_EQ(ids[0], "id2");
    EXPECT_EQ(ids[1], "id3");
    EXPECT_EQ(ids[2], "id1");

    std::remove("test_input_small.txt");
}

TEST_F(ProcessTopScoresTest, EmptyInputFile)
{
    std::ofstream inFile("test_input_empty.txt");
    inFile.close();
    setenv("INPUT_FILENAME", "test_input_empty.txt", 1);

    postprocess();

    // Find the created output file
    std::string outputFile = "test_output.txt";

    ASSERT_FALSE(outputFile.empty()) << "Output file not found";

    std::ifstream outFile(outputFile);
    std::string content((std::istreambuf_iterator<char>(outFile)),
                        std::istreambuf_iterator<char>());

    EXPECT_TRUE(content.empty()) << "Expected empty output file";

    std::remove("test_input_empty.txt");
}

TEST_F(ProcessTopScoresTest, InvalidInputFile)
{
    postprocess();

    // Check that no output file was created
    bool outputFileExists = false;
    for (const auto &entry : std::filesystem::directory_iterator("."))
    {
        if (std::regex_match(entry.path().filename().string(), std::regex("test_output_invalid_\\d{8}_\\d{6}\\.txt")))
        {
            outputFileExists = true;
            filesToRemove.push_back(entry.path().string());
            break;
        }
    }

    EXPECT_FALSE(outputFileExists) << "No output file should be created for an invalid input file.";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
