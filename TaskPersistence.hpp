#ifndef TASK_PERSISTENCE_HPP
#define TASK_PERSISTENCE_HPP

#include "Task.hpp"  // 包含 Task_Stru 定义
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <exception>

class TaskPersistence {
public:
    // 构造函数：允许自定义文件名（便于测试）
    explicit TaskPersistence(
        const std::string& activeFile = "active_tasks.txt",
        const std::string& completedFile = "completed_tasks.txt",
        char delimiter = '|'
    ) : activeFile_(activeFile),
        completedFile_(completedFile),
        delimiter_(delimiter) {}

    // ===== 主要持久化接口 =====
    bool loadActiveTasks(Task_Stru& tasks);
    bool loadCompletedTasks(Task_Stru& tasks);
    bool saveActiveTasks(const Task_Stru& tasks);
    bool saveCompletedTasks(const Task_Stru& tasks);

    // ===== 任务迁移 =====
    bool moveTaskToCompleted(Task_Stru& activeManager, Task_Stru& completedManager, int taskId);
    bool moveTaskToActive(Task_Stru& activeManager, Task_Stru& completedManager, int taskId);

    // ===== 文件管理 =====
    bool backupDataFiles();
    void listDataFiles();
    bool clearActiveFile();
    bool clearCompletedFile();

    // ===== 工具函数（公开，方便创建任务）=====
    static Task_data createTask(
        const std::string& title,
        const std::string& note = "",
        int deadline = 0,
        int priority = 5,
        bool finished = false
    );

    int getNextAvailableId(const Task_Stru& active, const Task_Stru& completed) const;

private:
    // ===== 配置 =====
    std::string activeFile_;
    std::string completedFile_;
    char delimiter_;

    // ===== 核心 I/O =====
    bool loadDataFromFile(Task_Stru& tasks, const std::string& filename);
    bool saveDataToFile(const Task_Stru& tasks, const std::string& filename) const;

    // ===== 辅助工具（私有）=====
    static std::string trim(const std::string& str);
    std::vector<std::string> split(const std::string& str) const;
    static std::string getCurrentDateTime();
    static bool isLeapYear(int year);
    static bool isValidDate(int year, int month, int day);
    static bool isValidTime(int hour, int minute);
    static bool validateDateTimeFormat(const std::string& datetimeStr);
    static int stringToDateTime(const std::string& datetimeStr);
    static std::string dateTimeToString(int datetime);
};

#endif // TASK_PERSISTENCE_HPP