#include "TaskPersistence.hpp"
#include <filesystem>  // C++17, for backup
#include <algorithm>

// ==================== 工具函数 ====================

std::string TaskPersistence::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> TaskPersistence::split(const std::string& str) const {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter_)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

std::string TaskPersistence::getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(4) << (localTime->tm_year + 1900)
       << std::setw(2) << (localTime->tm_mon + 1)
       << std::setw(2) << localTime->tm_mday
       << std::setw(2) << localTime->tm_hour
       << std::setw(2) << localTime->tm_min;
    return ss.str();
}

bool TaskPersistence::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool TaskPersistence::isValidDate(int year, int month, int day) {
    if (year < 2000 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    return (day >= 1 && day <= daysInMonth[month - 1]);
}

bool TaskPersistence::isValidTime(int hour, int minute) {
    return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

bool TaskPersistence::validateDateTimeFormat(const std::string& datetimeStr) {
    if (datetimeStr.length() != 12) return false;
    for (char c : datetimeStr) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    int year = std::stoi(datetimeStr.substr(0, 4));
    int month = std::stoi(datetimeStr.substr(4, 2));
    int day = std::stoi(datetimeStr.substr(6, 2));
    int hour = std::stoi(datetimeStr.substr(8, 2));
    int minute = std::stoi(datetimeStr.substr(10, 2));
    return isValidDate(year, month, day) && isValidTime(hour, minute);
}

int TaskPersistence::stringToDateTime(const std::string& datetimeStr) {
    if (datetimeStr == "0" || datetimeStr.empty()) return 0;
    if (!validateDateTimeFormat(datetimeStr)) {
        std::cerr << "警告: 日期时间格式无效: " << datetimeStr << std::endl;
        return 0;
    }
    return std::stoi(datetimeStr);
}

std::string TaskPersistence::dateTimeToString(int datetime) {
    if (datetime == 0) return "无截止时间";
    std::string s = std::to_string(datetime);
    if (s.length() != 12) return "无效时间";
    return s.substr(0, 4) + "-" +
           s.substr(4, 2) + "-" +
           s.substr(6, 2) + " " +
           s.substr(8, 2) + ":" +
           s.substr(10, 2);
}

// ==================== 公共接口 ====================

bool TaskPersistence::loadActiveTasks(Task_Stru& tasks) {
    return loadDataFromFile(tasks, activeFile_);
}

bool TaskPersistence::loadCompletedTasks(Task_Stru& tasks) {
    return loadDataFromFile(tasks, completedFile_);
}

bool TaskPersistence::saveActiveTasks(const Task_Stru& tasks) {
    return saveDataToFile(tasks, activeFile_);
}

bool TaskPersistence::saveCompletedTasks(const Task_Stru& tasks) {
    return saveDataToFile(tasks, completedFile_);
}

// ==================== 核心 I/O 实现 ====================

bool TaskPersistence::loadDataFromFile(Task_Stru& tasks, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // 文件不存在视为成功（空列表）
        return true;
    }

    // 清空现有任务（调用 createList）
    tasks.createList();

    std::string line;
    int lineNum = 0;
    int loadedCount = 0;

    while (std::getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto fields = split(line);
        if (fields.size() != 7) {
            std::cerr << "警告: 第 " << lineNum << " 行字段数量错误" << std::endl;
            continue;
        }

        try {
            Task_data task;
            task.id = std::stoi(fields[0]);
            task.title = fields[1];
            task.priority = std::stoi(fields[2]);
            if (task.priority < 1 || task.priority > 10) {
                std::cerr << "警告: 第 " << lineNum << " 行优先级超出范围(1-10)，已调整为5" << std::endl;
                task.priority = 5;
            }
            task.startline = stringToDateTime(fields[3]);
            task.deadline = stringToDateTime(fields[4]);

            std::string finishedStr = fields[5];
            task.finished = (finishedStr == "1" || finishedStr == "true" || finishedStr == "是");

            task.note = fields[6];

            tasks.InsertNode(task); // 使用你的 InsertNode(const Task_data&)
            ++loadedCount;

        } catch (const std::exception& e) {
            std::cerr << "警告: 第 " << lineNum << " 行数据格式错误: " << e.what() << std::endl;
            continue;
        }
    }

    file.close();
    std::string type = (filename == completedFile_) ? "已完成" : "未完成";
    std::cout << "从 " << filename << " 加载了 " << loadedCount << " 个" << type << "任务" << std::endl;
    return true;
}

bool TaskPersistence::saveDataToFile(const Task_Stru& tasks, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "错误: 无法创建/打开文件 " << filename << std::endl;
        return false;
    }

    file << "# 任务数据文件" << std::endl;
    file << "# 格式: id|title|priority|startline|deadline|finished|note" << std::endl;
    file << "# 日期格式: YYYYMMDDHHMM (年月日时分)" << std::endl;
    file << "# finished: 0=未完成, 1=已完成" << std::endl;
    file << std::endl;

    int savedCount = 0;
    TNode_head head = tasks.getHead();
    if (!head) {
        file.close();
        return true; // 空列表也算成功
    }

    TNode_elem* current = head->first;
    while (current) {
        const auto& task = current->task;
        bool shouldSave = (filename == completedFile_) ? task.finished : !task.finished;
        if (shouldSave) {
            file << task.id << delimiter_
                 << task.title << delimiter_
                 << task.priority << delimiter_
                 << task.startline << delimiter_
                 << task.deadline << delimiter_
                 << (task.finished ? "1" : "0") << delimiter_
                 << task.note << std::endl;
            ++savedCount;
        }
        current = current->next;
    }

    file.close();
    std::string type = (filename == completedFile_) ? "已完成" : "未完成";
    std::cout << "保存了 " << savedCount << " 个" << type << "任务到 " << filename << std::endl;
    return true;
}

// ==================== 任务迁移 ====================

bool TaskPersistence::moveTaskToCompleted(Task_Stru& activeManager, Task_Stru& completedManager, int taskId) {
    // 假设 Task_Stru 有按 ID 获取任务的方法（若无，可遍历）
    TNode_head head = activeManager.getHead();
    if (!head) return false;

    TNode_elem* current = head->first;
    while (current) {
        if (current->task.id == taskId) {
            Task_data task = current->task;
            task.finished = true;
            activeManager.DeleteNode(taskId);
            completedManager.InsertNode(task);
            std::cout << "任务 ID " << taskId << " 已标记为完成" << std::endl;
            return true;
        }
        current = current->next;
    }
    std::cerr << "未找到任务 ID: " << taskId << std::endl;
    return false;
}

bool TaskPersistence::moveTaskToActive(Task_Stru& activeManager, Task_Stru& completedManager, int taskId) {
    TNode_head head = completedManager.getHead();
    if (!head) return false;

    TNode_elem* current = head->first;
    while (current) {
        if (current->task.id == taskId) {
            Task_data task = current->task;
            task.finished = false;
            completedManager.DeleteNode(taskId);
            activeManager.InsertNode(task);
            std::cout << "任务 ID " << taskId << " 已重新标记为未完成" << std::endl;
            return true;
        }
        current = current->next;
    }
    std::cerr << "未找到任务 ID: " << taskId << std::endl;
    return false;
}

// ==================== 文件管理 ====================

bool TaskPersistence::backupDataFiles() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << "backup_"
        << std::put_time(&tm, "%Y%m%d_%H%M%S");

    std::string prefix = oss.str();
    try {
        std::filesystem::copy_file(activeFile_, prefix + "_active.txt", std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(completedFile_, prefix + "_completed.txt", std::filesystem::copy_options::overwrite_existing);
        std::cout << "备份成功: " << prefix << "_{active,completed}.txt" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "备份失败: " << e.what() << std::endl;
        return false;
    }
}

void TaskPersistence::listDataFiles() {
    std::cout << "\n=== 数据文件列表 ===" << std::endl;
    auto checkFile = [](const std::string& name) {
        std::ifstream f(name);
        if (f) {
            f.seekg(0, std::ios::end);
            std::cout << "✓ " << name << " (" << f.tellg() << " 字节)" << std::endl;
        } else {
            std::cout << "✗ 未找到文件: " << name << std::endl;
        }
    };
    checkFile(activeFile_);
    checkFile(completedFile_);
}

bool TaskPersistence::clearActiveFile() {
    std::ofstream file(activeFile_, std::ios::trunc);
    if (!file) return false;
    file << "# 任务数据文件 (已清空)" << std::endl;
    file << "# 格式: id|事项标题|优先级|开始时间|截至时间|是否完成|备注" << std::endl;
    file.close();
    std::cout << "已清空文件: " << activeFile_ << std::endl;
    return true;
}

bool TaskPersistence::clearCompletedFile() {
    std::ofstream file(completedFile_, std::ios::trunc);
    if (!file) return false;
    file << "# 任务数据文件 (已清空)" << std::endl;
    file << "# 格式: id|事项标题|优先级|开始时间|截至时间|是否完成|备注" << std::endl;
    file.close();
    std::cout << "已清空文件: " << completedFile_ << std::endl;
    return true;
}

// ==================== 工具函数 ====================

Task_data TaskPersistence::createTask(
    const std::string& title,
    const std::string& note,
    int deadline,
    int priority,
    bool finished
) {
    Task_data task;
    task.id = 0; // 由 getNextAvailableId 决定
    task.title = title;
    task.note = note;
    task.startline = std::stoi(getCurrentDateTime());

    if (deadline != 0) {
        std::string ds = std::to_string(deadline);
        if (!validateDateTimeFormat(ds)) {
            std::cerr << "警告: 截止时间格式无效，已设置为无截止时间" << std::endl;
            deadline = 0;
        }
    }
    task.deadline = deadline;

    task.priority = std::clamp(priority, 1, 10); // C++17
    // 若无 clamp: task.priority = (priority < 1) ? 1 : (priority > 10 ? 10 : priority);

    task.finished = finished;
    return task;
}

int TaskPersistence::getNextAvailableId(const Task_Stru& active, const Task_Stru& completed) const {
    int maxId = 0;
    auto scan = [&](const Task_Stru& tasks) {
        TNode_head h = tasks.getHead();
        if (h) {
            for (TNode_elem* p = h->first; p; p = p->next) {
                if (p->task.id > maxId) maxId = p->task.id;
            }
        }
    };
    scan(active);
    scan(completed);
    return maxId + 1;
}