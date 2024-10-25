#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int preprocess()
{
    vector<pair<string, string>> messages = parseMessages("result.json");
    for (const auto& [username, text] : messages) {
        cout << "Username: " << username << ", Message: " << text << endl;
    }
    return 0;
}

// Function to parse JSON and create a list of tuples (username, message)
vector<pair<string, string>> parseMessages(const string& filename) {
    vector<pair<string, string>> result;
    ifstream file(filename);
    json j;
    file >> j;

    for (const auto& message : j["messages"]) {
        if (message["type"] == "message") {
            string username = message["from"];
            string text = message["text"];
            result.emplace_back(username, text);
        }
    }
    return result;
}
