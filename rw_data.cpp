#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define FILENAME "task_data.txt"

class task {
    public:
        int id;
        string title;
        string description;
        bool isFinished = false;
};

string readTaskFile() {
    ifstream iFile(FILENAME);
    if (!iFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(iFile)), istreambuf_iterator<char>());
    iFile.close();
    return content;
}

string addTaskToFile(const task& newTask) {
    // Find the max ID in the file
    int maxId = 0;
    ifstream iFile(FILENAME);
    string line;
    while (getline(iFile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            int id = stoi(line.substr(0, pos));
            if (id > maxId) maxId = id;
        }
    }
    iFile.close();

    // Assign new ID (ignore newTask.id, auto-increment)
    int newId = maxId + 1;

    ofstream outFile(FILENAME, ios::app);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return "Error";
    }

    // Check if file is not empty and last character is not a newline
    ifstream checkFile2(FILENAME);
    checkFile2.seekg(0, ios::end);
    if (checkFile2.tellg() > 0) {
        checkFile2.seekg(-1, ios::end);
        char lastChar;
        checkFile2.get(lastChar);
        if (lastChar != '\n') {
            outFile << '\n';
        }
    }
    checkFile2.close();

    outFile << newId << ";" << newTask.title << ";" << newTask.description << ";" << (newTask.isFinished ? "1" : "0");
    outFile.close();
    return "Task added successfully.";
}

int getNumberofTasks() {
    ifstream iFile(FILENAME);
    if (!iFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return 0;
    }
    int count = 0;
    string line;
    while (getline(iFile, line)) {
        if (!line.empty()) count++;
    }
    iFile.close();
    return count;
}

void editTaskFromFile(int taskId, const task& updatedTask) {
    ifstream iFile(FILENAME);
    if (!iFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return;
    }
    string content;
    string line;
    bool found = false;
    while (getline(iFile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            int id = stoi(line.substr(0, pos));
            if (id == taskId) {
                content += to_string(taskId) + ";" + updatedTask.title + ";" + updatedTask.description + ";" + (updatedTask.isFinished ? "Yes" : "No") + "\n";
                found = true;
            } else {
                content += line + "\n";
            }
        }
    }
    iFile.close();
    ofstream outFile(FILENAME);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return;
    }
    outFile << content;
    outFile.close();
    if (found) {
        cout << "Task edited successfully." << endl;
    } else {
        cout << "Task with ID " << taskId << " not found." << endl;
    }
}


void deleteTaskFromFile(int taskId) {
    ifstream iFile(FILENAME);
    if (!iFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return;
    }
    string content;
    string line;
    while (getline(iFile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            int id = stoi(line.substr(0, pos));
            if (id != taskId) content += line + "\n";
        }
    }
    iFile.close();
    ofstream outFile(FILENAME);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return;
    }
    outFile << content;
    outFile.close();
    cout << "Task deleted successfully." << endl;
}

void markTaskInFile(int taskId) {
    ifstream iFile(FILENAME);
    if (!iFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return;
    }
    string content;
    string line;
    bool found = false;
    while (getline(iFile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            int id = stoi(line.substr(0, pos));
            if (id == taskId) {
                // Parse the rest of the fields
                size_t pos1 = line.find(';', pos + 1);
                size_t pos2 = line.find(';', pos1 + 1);
                string title = line.substr(pos + 1, pos1 - pos - 1);
                string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string finishedStr = line.substr(pos2 + 1);
                bool finished = (finishedStr == "1");
                // Toggle the finished state
                bool newFinished = !finished;
                content += to_string(taskId) + ";" + title + ";" + description + ";" + (newFinished ? "1" : "0") + "\n";
                found = true;
            } else {
                content += line + "\n";
            }
        }
    }
    iFile.close();
    ofstream outFile(FILENAME);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << FILENAME << endl;
        return;
    }
    outFile << content;
    outFile.close();
    if (found) cout << "Task " << (content.find(";1\n") != string::npos ? "marked as finished" : "unmarked") 
        << " successfully." << endl;
    else cout << "Task with ID " << taskId << " not found." << endl;
}