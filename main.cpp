#include <iostream>
#include <string>

#include "input_process.cpp"
#include "rw_data.cpp"
using namespace std;

void viewMenu();
void addTask();
void editTask();
void deleteTask();
void markTask();

// To-Do: Main Function
// 1. Make an opening program;
// 2. Make that program accepts input from user for them to select actions;
int main () {
    system("cls");
    cout << "TO-DO LIST PROGRAM" << endl;

    // User Action Menu
    cout << "Select Action:" << endl;
    cout << "1. View Tasks" << endl
            << "2. Exit" << endl;

    string input;
    do {
        cout << "Input Action: ";
        getline(cin, input);

        int action = mainMenuInput(input);
        switch (action) {
            case 1:
            viewMenu();
            break;
            case 2:
            cout << "Exit Program" << endl;
            break;
            default:
            cout << "Invalid input. Please retry." << endl;
            break;
        }
        if (action == 1 || action == 2) {
            break;
        }
    } while (input.empty() || mainMenuInput(input) == 0);
    
    return 0;
}

void viewMenu() {
    system("cls");

    // Display all tasks
    cout << comprehensionProcessor(readTaskFile()) << endl;

    // User Action Menu
    cout << "Select Action:" << endl;
    cout << "1. Add Task" << endl
            << "2. Edit Task" << endl
            << "3. Delete Task" << endl
            << "4. Mark/Unmark Task" << endl
            << "5. Back to Main Menu" << endl;   
    string input;
    do {
        cout << "Input Action: ";
        getline(cin, input);

        int action = viewMenuInput(input);
        switch (action) {
            case 1:
            addTask();
            break;
            case 2:
            editTask();
            break;
            case 3:
            deleteTask();
            break;
            case 4:
            markTask();
            break;
            case 5:
            main();
            break;
            default:
            cout << "Invalid input. Please retry." << endl;
            break;
        }
        if (action >= 1 && action <= 5) {
            break;
        }
    } while (input.empty() || mainMenuInput(input) == 0);
}

void addTask() {
    task newTask;
    while (true) {
        cout << "Enter Task Title (max 25 chars): ";
        getline(cin, newTask.title);
        size_t find_semicolonn = newTask.title.find(';');
        if (find_semicolonn != string::npos) {
            cout << "Title cannot contain semicolon (;). Please re-enter." << endl;
            continue;
        }
        if (newTask.title.length() > 25) {
            cout << "Title too long. Please enter up to 25 characters." << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "Enter Task Description (max 100 chars): ";
        getline(cin, newTask.description);
        size_t find_semicolonn = newTask.description.find(';');
        if (find_semicolonn != string::npos) {
            cout << "Description cannot contain semicolon (;). Please re-enter." << endl;
            continue;
        }
        if (newTask.description.length() > 100) {
            cout << "Description too long. Please enter up to 100 characters." << endl;
            continue;
        }
        break;
    }
    newTask.isFinished = false;

    string result = addTaskToFile(newTask);
    cout << result << endl;
    viewMenu();
}

void editTask() {
    int taskId;
    task updatedTask;
    cout << "Enter Task ID/Number to edit:";
    while (!(cin >> taskId) || taskId < 0 || taskId > (getNumberofTasks() - 1)) {
        cout << "Invalid input. Please enter a valid Task ID/Number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.clear();
    cin.ignore(10000, '\n');
    while (true) {
        cout << "Enter New Task Title (max 25 chars): ";
        getline(cin, updatedTask.title);
        size_t find_semicolonn = updatedTask.title.find(';');
        if (find_semicolonn != string::npos) {
            cout << "Title cannot contain semicolon (;). Please re-enter." << endl;
            continue;
        }
        if (updatedTask.title.length() > 25) {
            cout << "Title too long. Please enter up to 25 characters." << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "Enter New Task Description (max 100 chars): ";
        getline(cin, updatedTask.description);
        size_t find_semicolonn = updatedTask.description.find(';');
        if (find_semicolonn != string::npos) {
            cout << "Description cannot contain semicolon (;). Please re-enter." << endl;
            continue;
        }
        if (updatedTask.description.length() > 100) {
            cout << "Description too long. Please enter up to 100 characters." << endl;
            continue;
        }
        break;
    }
    editTaskFromFile(taskId, updatedTask);
    viewMenu();
}

void deleteTask() {
    int taskId;
    cout << "Enter Task ID/Number to delete:";
    while (!(cin >> taskId) || taskId < 0 || taskId > (getNumberofTasks() - 1)) {
        cout << "Invalid input. Please enter a valid Task ID/Number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.clear();
    cin.ignore(10000, '\n');
    deleteTaskFromFile(taskId);
    viewMenu();
}

void markTask() {
    int taskId;
    cout << "Enter Task ID/Number to mark/unmark:";
    while (!(cin >> taskId) || taskId < 0 || taskId > (getNumberofTasks() - 1)) {
        cout << "Invalid input. Please enter a valid Task ID/Number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.clear();
    cin.ignore(10000, '\n');
    // markTaskInFile(taskId); // To-Do: Implement this function in rw_data.cpp
    markTaskInFile(taskId);
    viewMenu();
}