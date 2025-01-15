// =================================================================================
//
//   📋 TaskMaster C++
//
//   A Powerful Cross-Platform Task Management System
//   Created by: Shreenidhi V
//   GitHub: https://github.com/shreenxdhi/TaskMaster
//
// =================================================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>

// --- Cross-platform screen clearing ---
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

// Forward declaration
class TaskManager;

/**
 * @class Task
 * @brief Represents a single task with its properties.
 */
class Task {
private:
    std::string description;
    int priority;
    std::string dueDate;
    bool isDone;

public:
    // Constructor
    Task(std::string desc, int prio, std::string due, bool done = false)
        : description(std::move(desc)), priority(prio), dueDate(std::move(due)), isDone(done) {}

    // Getters
    std::string getDescription() const { return description; }
    int getPriority() const { return priority; }
    std::string getDueDate() const { return dueDate; }
    bool getIsDone() const { return isDone; }

    // Setters
    void setDescription(const std::string& desc) { description = desc; }
    void setPriority(int prio) { priority = prio; }
    void markDone() { isDone = true; }

    /**
     * @brief Prints the task details in a formatted way.
     */
    void print() const {
        std::cout << "  Description: " << description << "\n";
        std::cout << "  Priority:    " << priority << "\n";
        std::cout << "  Due Date:    " << (dueDate.empty() ? "N/A" : dueDate) << "\n";
        std::cout << "  Status:      " << (isDone ? "Completed" : "Pending") << "\n";
    }
};

/**
 * @class TaskManager
 * @brief Manages all tasks, including loading, saving, and user interactions.
 */
class TaskManager {
private:
    std::vector<Task> tasks;
    const std::string fileName = "tasks.json";

    /**
     * @brief Saves all current tasks to the JSON file.
     */
    void saveTasksToFile() {
        std::ofstream outFile(fileName);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open " << fileName << " for writing." << std::endl;
            return;
        }

        outFile << "{\n";
        outFile << "  \"tasks\": [\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            outFile << "    {\n";
            std::string escapedDesc = tasks[i].getDescription();
            size_t pos = 0;
            while ((pos = escapedDesc.find("\"", pos)) != std::string::npos) {
                escapedDesc.replace(pos, 1, "\\\"");
                pos += 2;
            }
            outFile << "      \"description\": \"" << escapedDesc << "\",\n";
            outFile << "      \"priority\": " << tasks[i].getPriority() << ",\n";
            outFile << "      \"dueDate\": \"" << tasks[i].getDueDate() << "\",\n";
            outFile << "      \"isDone\": " << (tasks[i].getIsDone() ? "true" : "false") << "\n";
            outFile << "    }" << (i == tasks.size() - 1 ? "" : ",");
            outFile << "\n";
        }
        outFile << "  ]\n";
        outFile << "}\n";
        outFile.close();
    }

    /**
     * @brief Loads tasks from the JSON file into memory.
     */
    void loadTasksFromFile() {
        std::ifstream inFile(fileName);
        if (!inFile.is_open()) {
            return; // File doesn't exist yet, will be created on save.
        }

        tasks.clear();
        std::string line, desc, due;
        int prio = 0;
        bool isDone = false;

        while (getline(inFile, line)) {
            if (line.find("\"description\"") != std::string::npos) {
                size_t start = line.find(": \"") + 3;
                size_t end = line.find_last_of("\"");
                desc = line.substr(start, end - start);
            } else if (line.find("\"priority\"") != std::string::npos) {
                size_t start = line.find(": ") + 2;
                try {
                    prio = std::stoi(line.substr(start));
                } catch (const std::invalid_argument&) {
                    prio = 1; // Default priority on error
                }
            } else if (line.find("\"dueDate\"") != std::string::npos) {
                size_t start = line.find(": \"") + 3;
                size_t end = line.find_last_of("\"");
                due = line.substr(start, end - start);
            } else if (line.find("\"isDone\"") != std::string::npos) {
                isDone = (line.find("true") != std::string::npos);
                tasks.emplace_back(desc, prio, due, isDone);
            }
        }
        inFile.close();
    }
    
    /**
     * @brief Gets the actual index of a task in the main `tasks` vector from its displayed index.
     * @param displayIndex The 1-based index shown to the user.
     * @param isForPendingTasks True if the index is for a pending task, false for completed.
     * @return The 0-based index in the `tasks` vector, or -1 if not found.
     */
    int getOriginalIndex(int displayIndex, bool isForPendingTasks) {
        std::vector<int> indices;
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].getIsDone() != isForPendingTasks) {
                indices.push_back(i);
            }
        }

        // Sort indices based on task priority to match display order
        std::sort(indices.begin(), indices.end(), [&](int a, int b) {
            return tasks[a].getPriority() > tasks[b].getPriority();
        });

        if (displayIndex > 0 && static_cast<size_t>(displayIndex) <= indices.size()) {
            return indices[displayIndex - 1];
        }
        return -1; // Not found
    }

public:
    TaskManager() {
        loadTasksFromFile();
    }

    /**
     * @brief Guides the user to add a new task.
     */
    void addTask() {
        std::string desc, due;
        int prio;

        std::cout << "Enter task description: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, desc);

        std::cout << "Enter priority (1-5, 5 is highest): ";
        while (!(std::cin >> prio) || prio < 1 || prio > 5) {
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter due date (YYYY-MM-DD) or leave blank: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, due);

        tasks.emplace_back(desc, prio, due);
        saveTasksToFile();
        std::cout << "\n\u2705 Task added successfully!\n";
        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
    
    /**
     * @brief Lists tasks, sorted by priority.
     * @param showCompleted True to show completed tasks, false for pending.
     */
    void listTasks(bool showCompleted) {
        std::vector<Task> toDisplay;
        for (const auto& task : tasks) {
            if (task.getIsDone() == showCompleted) {
                toDisplay.push_back(task);
            }
        }

        if (toDisplay.empty()) {
            std::cout << (showCompleted ? "\nNo completed tasks found." : "\nNo pending tasks found.") << std::endl;
            return;
        }
        
        std::sort(toDisplay.begin(), toDisplay.end(), [](const Task& a, const Task& b) {
            return a.getPriority() > b.getPriority();
        });

        std::cout << "\n--- " << (showCompleted ? "Completed" : "Pending") << " Tasks ---\n";
        for (size_t i = 0; i < toDisplay.size(); ++i) {
            std::cout << "Task #" << i + 1 << "\n";
            toDisplay[i].print();
            std::cout << "--------------------\n";
        }
    }

    /**
     * @brief Marks a pending task as complete.
     */
    void markTaskDone() {
        listTasks(false);
        long pendingCount = std::count_if(tasks.begin(), tasks.end(), [](const Task& t){ return !t.getIsDone(); });
        if (pendingCount == 0) return;

        std::cout << "\nEnter the Task # to mark as complete: ";
        int choice;
        std::cin >> choice;

        int original_index = getOriginalIndex(choice, true);

        if (original_index != -1) {
            tasks[original_index].markDone();
            saveTasksToFile();
            std::cout << "\n\u2705 Task marked as complete!\n";
        } else {
            std::cout << "\n\u274C Invalid task number.\n";
        }
    }

    /**
     * @brief Edits the description or priority of a pending task.
     */
    void editTask() {
        listTasks(false);
        long pendingCount = std::count_if(tasks.begin(), tasks.end(), [](const Task& t){ return !t.getIsDone(); });
        if (pendingCount == 0) return;

        std::cout << "\nEnter the Task # to edit: ";
        int choice;
        std::cin >> choice;

        int original_index = getOriginalIndex(choice, true);

        if (original_index != -1) {
            std::cout << "Editing Task: " << tasks[original_index].getDescription() << std::endl;
            
            std::cout << "Enter new description (or press Enter to keep current): ";
            std::string new_desc;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, new_desc);

            std::cout << "Enter new priority (1-5, or 0 to keep current): ";
            int new_prio;
            std::cin >> new_prio;

            if (!new_desc.empty()) {
                tasks[original_index].setDescription(new_desc);
            }
            if (new_prio >= 1 && new_prio <= 5) {
                tasks[original_index].setPriority(new_prio);
            }
            
            saveTasksToFile();
            std::cout << "\n\u2705 Task updated successfully!\n";
        } else {
            std::cout << "\n\u274C Invalid task number.\n";
        }
    }
    
    /**
     * @brief Deletes a task from the list.
     */
    void deleteTask() {
         listTasks(false); // Can delete from pending
         listTasks(true); // Or from completed
        if (tasks.empty()) {
            std::cout << "No tasks to delete.\n";
            return;
        }

        std::cout << "\nEnter the Task # to delete (from pending or completed list): ";
        int choice;
        std::cin >> choice;
        
        // Try to find in pending, then in completed
        int original_index = getOriginalIndex(choice, true); // Pending
        if (original_index == -1) {
            original_index = getOriginalIndex(choice, false); // Completed
        }
        
        if (original_index != -1) {
            tasks.erase(tasks.begin() + original_index);
            saveTasksToFile();
            std::cout << "\n\u2705 Task deleted successfully!\n";
        } else {
            std::cout << "\n\u274C Invalid task number.\n";
        }
    }
};

/**
 * @brief Prints the main menu to the console.
 */
void printMenu() {
    system(CLEAR_SCREEN);
    // Use the standard octal escape sequence '\033' for colors to avoid warnings
    std::cout << "\n\033[1;36mWelcome to TaskMaster C++!\033[0m\n";
    std::cout << "===========================\n";
    std::cout << " [1] Add a new task\n";
    std::cout << " [2] List pending tasks\n";
    std::cout << " [3] Mark a task as complete\n";
    std::cout << " [4] Edit a task\n";
    std::cout << " [5] Delete a task\n";
    std::cout << " [6] View completed tasks\n";
    std::cout << " [7] Exit\n\n";
    std::cout << "Enter your choice: ";
}

int main() {
    TaskManager tm;
    int choice;

    do {
        printMenu();
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: tm.addTask(); break;
            case 2: tm.listTasks(false); break;
            case 3: tm.markTaskDone(); break;
            case 4: tm.editTask(); break;
            case 5: tm.deleteTask(); break;
            case 6: tm.listTasks(true); break;
            case 7: std::cout << "\nExiting TaskMaster. Goodbye!\n" << std::endl; break;
            default: std::cout << "\nInvalid choice. Please try again.\n";
        }
        if (choice != 1 && choice != 7) {
             std::cout << "\nPress Enter to continue...";
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cin.get();
        }
    } while (choice != 7);

    return 0;
}