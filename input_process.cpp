#include <iostream>
#include <string>
#include <vector>

using namespace std;
using sint_vector = vector<pair<vector<string>, int>>;

int mainMenuInput(string input) {
    sint_vector validOptions = {
        {{"1", "View", "View Tasks"}, 1},
        {{"2", "Exit", "Quit", "Close"}, 2},
    };

    for (const auto& option : validOptions) {
        for (const string& validInput : option.first) {
            if (input == validInput) {
                return option.second; // Exit Program
            }
        }
    }
    return 0; // Invalid Input
}

int viewMenuInput(string input) {
    sint_vector validOptions = {
        {{"1", "Add", "Add Task", "add"}, 1},
        {{"2", "Edit", "Edit Task", "edit"}, 2},
        {{"3", "Delete", "Delete Task", "delete"}, 3},
        {{"4", "mark", "Mark Task", "finish"}, 4},
        {{"5", "back", "main", "main menu", "mennu"}, 5}
    };
    for (const auto& option : validOptions) {
        for (const std::string& validInput : option.first) {
            if (input == validInput) {
                return option.second;
            }
        }
    }
    return 0; // Invalid Input
}

string comprehensionProcessor(const string& rawData) {
    // Function that accepts readTaskFile output and processes it for better readability
    // Input format: "1;Task Title;Task Description;0\n2;Another Task;Another Description;1\n"
    // Output format: "1. [x] Task Title\n   Task Description\n". [X] if finished, [ ] if not finished
    string output;
    size_t start = 0;
    size_t end = rawData.find('\n');
    while (start < rawData.size()) {
        string line;
        if (end != string::npos) {
            line = rawData.substr(start, end - start);
        } else {
            line = rawData.substr(start);
        }

        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string id = line.substr(0, pos1);
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string description = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string isFinished = line.substr(pos3 + 1);

            output += id + ". [" + (isFinished == "1" ? "x" : " ") + "] " + title + "\n   " + description + "\n";
        }

        if (end == string::npos) break;
        start = end + 1;
        end = rawData.find('\n', start);
    }
    return output;
}