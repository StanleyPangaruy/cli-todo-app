#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Task {
  int id;
  string name;
  time_t time_stamp;
  bool isDone;
};

void printHelp() {
    cout << "---------------------------------------------------------\n";
    cout << "               📝 C++ TODO LIST APP HELP                 \n";
    cout << "---------------------------------------------------------\n";
    cout << "Usage: ./todo <command> [arguments]\n\n";
    cout << "Commands:\n";
    cout << "  add \"<task>\"    : Add a new task\n";
    cout << "                    Example: ./todo add \"Buy Milk\"\n\n";
    cout << "  list            : Show pending tasks\n";
    cout << "  list -a         : Show ALL tasks (including completed)\n\n";
    cout << "  complete <ID>   : Mark a task as finished\n";
    cout << "                    Example: ./todo complete 1\n\n";
    cout << "  delete <ID>     : Delete a task permanently\n";
    cout << "                    Example: ./todo delete 2\n";
    cout << "---------------------------------------------------------\n";
}

string getRelativeTime (time_t createdTime) {
  time_t now = time(nullptr);
  double seconds = difftime(now, createdTime);

  if (seconds < 60) {
    return "a few seconds ago";
  } else if (seconds < 3600) {
    int minutes = seconds / 60;
    return to_string(minutes) + " minute" + (minutes > 1 ? "s" : "") + " ago";
  } else if (seconds < 86400) {
    int hours = seconds / 3600;
    return to_string(hours) + " hour" + (hours > 1 ? "s" : "") + " ago";
  } else {
    int days = seconds / 86400;
    return to_string(days) + " day" + (days > 1 ? "s" : "") + " ago";
  }
}

int main (int argc, char* argv[]) {
  if (argc == 1) {
    printHelp(); 
    return 1;
  }
  
  string command = argv[1];

  if (command == "add") {
    if (argc < 3) {
      cout << "error: missing task description!";
      return 1;
    }
    
    time_t now = time(nullptr);
    ofstream file("tasks.csv", ios::app);
    file << argv[2] << "," << now << "," << "0" << "\n";
    cout << "Task added successfully!" << "\n";
    
  } 
  else if (command == "list") {
    bool showAll = false;

    if (argc > 2) {
      string flag = argv[2];
      if (flag == "-a" || flag == "--all") {
        showAll = true;
      }
    }

    ifstream file("tasks.csv");
    string line;
    int id = 1;

    cout << left << setw(5) << "ID"
         << left << setw(40) << "Task"
         << left << setw(20) << "Created"
         << left << setw(10) << "Done" << "\n";
    cout << string(75, '-') << "\n";

    while (getline(file, line)) {
      size_t firstComma = line.find_last_of(',');
      size_t secondComma = line.find_last_of(',', firstComma - 1);

      string task = line.substr(0, secondComma);
      string timeStr = line.substr(secondComma + 1, firstComma - secondComma - 1);
      string doneStr = line.substr(firstComma + 1);

      bool isDone = (doneStr == "1");

      if (isDone && !showAll) {
        id++;
        continue;
      }

      time_t createdTime = (time_t)stol(timeStr);
      string friendlyTime = getRelativeTime(createdTime);

      cout << left << setw(5) << id
           << left << setw(40) << task
           << left << setw(20) << friendlyTime
           << left << setw(10) << (isDone ? "true" : "false") << "\n";

      id++;
    }
  }
  else if (command == "complete") {
    if (argc < 3) {
      cout << "Error: Missing task ID!" << "\n";
      return 1;
    }

    int targetId = stoi(argv[2]);
    vector<Task> tasks;
    string line;
    
    ifstream inFile("tasks.csv");
    if (!inFile) {
        cout << "Error: Could not open tasks.csv" << "\n";
        return 1;
    }

    int currentId = 1;
    bool found = false;

    while (getline(inFile, line)) {
      size_t firstComma = line.find_last_of(',');
      size_t secondComma = line.find_last_of(',', firstComma - 1);
        
      string name = line.substr(0, secondComma);
      string timeStr = line.substr(secondComma + 1, firstComma - secondComma - 1);
      string doneStr = line.substr(firstComma + 1);
        
      Task t;
      t.id = currentId;
      t.name = name;
      t.time_stamp = (time_t)stol(timeStr);
      t.isDone = (doneStr == "1");

      if (currentId == targetId) {
        t.isDone = true;
        found = true;
      }

      tasks.push_back(t);
      currentId++;
    }
    inFile.close();

    if (!found) {
      cout << "Error: Task ID " << targetId << " not found." << "\n";
      return 1;
    }

    ofstream outFile("tasks.csv", ios::trunc);
    
    for (const auto& t : tasks) {
      outFile << t.name << "," << t.time_stamp << "," << (t.isDone ? "1" : "0") << "\n";
    }
    
    cout << "Task " << targetId << " marked as complete!" << "\n";
  } 
  else if (command == "delete") {
    if (argc < 3) {
      cout << "Error: Missing Task ID!" << "\n";
      return 1;
    }

    int targetId = stoi(argv[2]);
    vector<Task> tasks;
    string line;
    
    ifstream inFile("tasks.csv");
    if (!inFile) {
      cout << "Error: Could not open tasks.csv" << "\n";
      return 1;
    }

    int currentId = 1;
    bool found = false;

    while (getline(inFile, line)) {
      size_t firstComma = line.find_last_of(',');
      size_t secondComma = line.find_last_of(',', firstComma - 1);
        
      string name = line.substr(0, secondComma);
      string timeStr = line.substr(secondComma + 1, firstComma - secondComma - 1);
      string doneStr = line.substr(firstComma + 1);
        
      if (currentId == targetId) {
        found = true;
        cout << "Task deleted: " << name << "\n";
      } else {
        Task t;
        t.name = name;
        t.time_stamp = (time_t)stol(timeStr);
        t.isDone = (doneStr == "1");
        tasks.push_back(t);
      }

      currentId++;
    }
    inFile.close();

    if (!found) {
      cout << "Error: Task ID " << targetId << " not found." << "\n";
      return 1;
    }

    ofstream outFile("tasks.csv", ios::trunc);
    
    for (const auto& t : tasks) {
      outFile << t.name << "," << t.time_stamp << "," << (t.isDone ? "1" : "0") << "\n";
    }
    
    cout << "Task " << targetId << " has been deleted!" << "\n";
  }
  return 0;
}
