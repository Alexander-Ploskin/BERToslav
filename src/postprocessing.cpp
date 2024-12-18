#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cstdlib> // for getenv

void postprocess()
{
    // Get filenames from environment variables
    const char *inputFilename = std::getenv("INPUT_FILENAME");
    const char *outputFilename = std::getenv("OUTPUT_FILENAME");

    if (!inputFilename || !outputFilename)
    {
        std::cerr << "Error: INPUT_FILENAME and OUTPUT_FILENAME environment variables must be set." << std::endl;
        return;
    }

    // Read the dictionary from file
    std::ifstream inFile(inputFilename);
    if (!inFile)
    {
        std::cerr << "Error opening input file: " << inputFilename << std::endl;
        return;
    }

    std::map<std::string, int> scoreMap;
    std::string line, id;
    int score;

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        if (iss >> id >> score)
        {
            scoreMap[id] = score;
        }
    }
    inFile.close();

    // Sort the scores
    std::vector<std::pair<std::string, int>> sortedScores(scoreMap.begin(), scoreMap.end());
    std::sort(sortedScores.begin(), sortedScores.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
              { return a.second > b.second; });

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
    std::string timestamp = ss.str();

    // Write top 5 IDs to file
    std::string fullOutputFilename = std::string(outputFilename); //+ "_" + timestamp + ".txt";
    std::ofstream outFile(fullOutputFilename);
    if (!outFile)
    {
        std::cerr << "Error opening output file: " << fullOutputFilename << std::endl;
        return;
    }

    for (int i = 0; i < 5 && i < sortedScores.size(); ++i)
    {
        outFile << sortedScores[i].first << std::endl;
    }
    outFile.close();

    std::cout << "Top 5 IDs written to " << fullOutputFilename << std::endl;
}
