# 📝 C++ CLI To-Do List

A simple, fast, and persistent command-line to-do list application built with C++. 
It saves your tasks to a local CSV file so you never lose track of your work, even after closing the terminal.

## 🚀 Features

* **Persistent Storage:** Tasks are saved in `tasks.csv`.
* **Task Management:** Add, List, Complete, and Delete tasks.
* **Time Tracking:** See exactly how long ago a task was created (e.g., "2 minutes ago").
* **Filter Views:** Toggle between seeing pending tasks or the full history.
* **Smart Parsing:** Handles CSV data reading and writing manually.

## 🛠️ How to Build

You need a C++ compiler (like G++) installed.

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/StanleyPangaruy/cpp-todo-list.git
    cd cpp-todo-list
    ```

2.  **Compile the code:**
    ```bash
    g++ todo.cpp -o todo
    ```

3.  **Run the app:**
    ```bash
    ./todo
    ```

## 📖 Usage Guide

### 1. Help Menu
View all available commands.
```bash
./todo help
