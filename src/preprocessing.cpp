#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Function to parse CSV and create a list of tuples (username, message)
vector<pair<string, string>> parseMessages(const string& filename) {
    vector<pair<string, string>> result;
    ifstream file(filename);
    string line;
    // Assuming the first line is the header
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string username, text;
        getline(ss, username, ','); // Read 'from' column
        getline(ss, text);          // Read 'text' column
        result.emplace_back(username, text);
    }
    return result;
}

// Function to save messages to a CSV file
void saveMessagesToCSV(const vector<pair<string, string>>& messages, const string& filename) {
    ofstream file(filename);
    file << "from,text\n"; // Write header
    for (const auto& [username, text] : messages) {
        file << username << "," << text << "\n";
    }
}

int preprocess()
{
    vector<pair<string, string>> messages = parseMessages("input.csv");
    saveMessagesToCSV(messages, "output.csv");
    return 0;
}
