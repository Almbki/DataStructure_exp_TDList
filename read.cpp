#include "read.h"
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}
// 分割字符串
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    
    return tokens;
}
// 获取当前日期时间字符串 (格式: YYYYMMDDHHMM)
string getCurrentDateTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    
    stringstream ss;
    ss << setfill('0') 
       << setw(4) << (localTime->tm_year + 1900)
       << setw(2) << (localTime->tm_mon + 1)
       << setw(2) << localTime->tm_mday
       << setw(2) << localTime->tm_hour
       << setw(2) << localTime->tm_min;
    
    return ss.str();
}
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool isValidDate(int year, int month, int day) {
    if (year < 2000 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // 处理闰年二月
    if (month == 2 && isLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }
    
    return true;
}
// 验证时间有效性
bool isValidTime(int hour, int minute) {
    return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}
bool validateDateTimeFormat(const string& datetimeStr) {
    if (datetimeStr.length() != 12) {
        return false;
    }
    for (char c : datetimeStr) {
        if (!isdigit(c)) {
            return false;
        }
    }
    int year = stoi(datetimeStr.substr(0, 4));
    int month = stoi(datetimeStr.substr(4, 2));
    int day = stoi(datetimeStr.substr(6, 2));
    int hour = stoi(datetimeStr.substr(8, 2));
    int minute = stoi(datetimeStr.substr(10, 2));
    if (!isValidDate(year, month, day)) {
        return false;
    }
    if (!isValidTime(hour, minute)) {
        return false;
    }
    return true;
}
int stringToDateTime(const string& datetimeStr) {
    if (datetimeStr == "0" || datetimeStr.empty()) {
        return 0;
    }  
    if (!validateDateTimeFormat(datetimeStr)) {
        cerr << "警告: 日期时间格式无效: " << datetimeStr << endl;
        return 0;
    }
    
    return stoi(datetimeStr);
}
string dateTimeToString(int datetime) {
    if (datetime == 0) {
        return "无截止时间";
    } 
    string datetimeStr = to_string(datetime);
    if (datetimeStr.length() != 12) {
        return "无效时间";
    }
    return datetimeStr.substr(0, 4) + "-" + 
           datetimeStr.substr(4, 2) + "-" + 
           datetimeStr.substr(6, 2) + " " + 
           datetimeStr.substr(8, 2) + ":" + 
           datetimeStr.substr(10, 2);
}
int getNextAvailableId(Task_Stru& taskManager, bool checkCompleted) {
    int maxId = 0;
    TNode_head head = taskManager.getHead();
    if (!head) {
        return 1; // 链表为空，从1开始
    }
    
    // 遍历链表查找最大ID
    TNode_elem* current = head->first;
    while (current != nullptr) {
        if (current->task.id > maxId) {
            maxId = current->task.id;
        }
        current = current->next;
    }
    return maxId + 1;
}
Task_data createTask(const string& title, const string& note, 
                     int deadline, int priority, bool finished) {
    Task_data newTask;
    newTask.id = 0; 
    newTask.title = title;
    newTask.note = note;
    newTask.startline = stoi(getCurrentDateTime()); // 自动设置创建时间
    
    // 验证截止时间
    if (deadline != 0) {
        string deadlineStr = to_string(deadline);
        if (!validateDateTimeFormat(deadlineStr)) {
            cerr << "警告: 截止时间格式无效，已设置为无截止时间" << endl;
            deadline = 0;
        }
    }
    newTask.deadline = deadline;

    //确保优先级在1-10之间
    if (priority < 1) priority = 1;
    if (priority > 10) priority = 10;
    newTask.priority = priority;
    
    newTask.finished = finished;
    
    return newTask;
}

// 从文件加载数据
bool loadDataFromFile(Task_Stru& taskManager, bool loadCompleted, const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "无法打开文件 " << filename << endl;
        return false;
    }
    // 清空链表
    taskManager.createList();
    string line;
    int lineNum = 0;
    int loadedCount = 0;
    
    // 读取文件头
    while (getline(file, line)) {
        lineNum++;
        line = trim(line);
        
        // 跳过空行和注释
        if (line.empty() || line[0] == '#') {
            continue;
        }
        // 解析数据行
        vector<string> fields = split(line, DELIMITER);
        try {
            Task_data task;
            task.id = stoi(fields[0]);
            task.title = fields[1];
            task.priority = stoi(fields[2]);
            //检查优先级是否合法
            if (task.priority < 1 || task.priority > 10) {
                cerr << "警告: 第" << lineNum << "行优先级超出范围(1-10)，已调整为5" << endl;
                task.priority = 5;
            }
            
            // 解析日期时间
            task.startline = stringToDateTime(fields[3]);
            task.deadline = stringToDateTime(fields[4]);
            
            // 解析完成状态
            string finishedStr = fields[5];
            if (finishedStr == "1" || finishedStr == "true" || finishedStr == "是") {
                task.finished = true;
            } else {
                task.finished = false;
            }
            
            task.note = fields[6];
            
            // 创建新节点
            TNode_elem* newNode = new TNode_elem;
            newNode->task = task;
            newNode->next = nullptr;
            newNode->prior = nullptr;
            
            // 插入链表
            taskManager.InsertNode(newNode);
            loadedCount++;
            
        } catch (const exception& e) {
            cerr << "警告: 第" << lineNum << "行数据格式错误: " << e.what() << endl;
            continue;
        }
    }
    
    file.close();
    
    string taskType = loadCompleted ? "已完成" : "未完成";
    cout << "从 " << filename << " 加载了 " << loadedCount << " 个" << taskType << "任务" << endl;
    
    return true;
}

// 保存数据到文件
bool saveDataToFile(Task_Stru& taskManager, bool saveCompleted, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "错误: 无法创建/打开文件 " << filename << endl;
        return false;
    }
    
    // 写入文件头
    file << "# 任务数据文件" << endl;
    file << "# 格式: id|title|priority|startline|deadline|finished|note" << endl;
    file << "# 日期格式: YYYYMMDDHHMM (年月日时分)" << endl;
    file << "# finished: 0=未完成, 1=已完成" << endl;
    file << endl;
    
    // 获取链表头
    TNode_head head = taskManager.getHead();
    if (!head) {
        cerr << "错误: 任务管理器为空" << endl;
        file.close();
        return false;
    }
    // 遍历链表
    TNode_elem* current = head->first;
    int savedCount = 0;
    
    while (current != nullptr) {
        const Task_data& task = current->task;
        
        // 根据要保存的类型过滤任务
        if ((saveCompleted && task.finished) || (!saveCompleted && !task.finished)) {
            file << task.id << DELIMITER
                 << task.title << DELIMITER
                 << task.priority << DELIMITER
                 << task.startline << DELIMITER
                 << task.deadline << DELIMITER
                 << (task.finished ? "1" : "0") << DELIMITER
                 << task.note << endl;
            
            savedCount++;
        }
        
        current = current->next;
    }
    
    file.close();
    
    string taskType = saveCompleted ? "已完成" : "未完成";
    cout << "保存了 " << savedCount << " 个" << taskType << "任务到 " << filename << endl;
    
    return (savedCount > 0 || head->length == 0);
}

// 将任务从未完成移动到已完成
bool moveTaskToCompleted(Task_Stru& activeManager, Task_Stru& completedManager, int taskId) {
    // 获取未完成任务链表的头
    TNode_head activeHead = activeManager.getHead();
    if (!activeHead) {
        cerr << "错误: 未完成任务管理器为空" << endl;
        return false;
    }
    
    // 查找任务
    TNode_elem* current = activeHead->first;
    while (current != nullptr) {
        if (current->task.id == taskId) {
            // 标记为已完成
            current->task.finished = true;
            
            // 从未完成任务链表中删除
            activeManager.DeleteNode(taskId);
            
            // 添加到已完成任务链表
            TNode_elem* newNode = new TNode_elem;
            newNode->task = current->task;
            newNode->next = nullptr;
            newNode->prior = nullptr;
            
            completedManager.InsertNode(newNode);
            
            cout << "任务 ID " << taskId << " 已标记为完成" << endl;
            return true;
        }
        current = current->next;
    }
    
    cerr << "未找到任务 ID: " << taskId << endl;
    return false;
}

// 将任务从已完成移动到未完成
bool moveTaskToActive(Task_Stru& activeManager, Task_Stru& completedManager, int taskId) {
    // 获取已完成任务链表的头
    TNode_head completedHead = completedManager.getHead();
    if (!completedHead) {
        cerr << "错误: 已完成任务管理器为空" << endl;
        return false;
    }
    
    // 查找任务
    TNode_elem* current = completedHead->first;
    while (current != nullptr) {
        if (current->task.id == taskId) {
            // 标记为未完成
            current->task.finished = false;
            // 从已完成任务链表中删除
            completedManager.DeleteNode(taskId);
            // 添加到未完成任务链表
            TNode_elem* newNode = new TNode_elem;
            newNode->task = current->task;
            newNode->next = nullptr;
            newNode->prior = nullptr;
            activeManager.InsertNode(newNode);
            cout << "任务 ID " << taskId << " 已重新标记为未完成" << endl;
            return true;
        }
        current = current->next;
    }
    cerr << "未找到任务 ID: " << taskId << endl;
    return false;
}

// 备份数据文件
bool backupDataFiles() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    
    // 生成备份文件名
    stringstream backupName;
    backupName << "backup_" << put_time(localTime, "%Y%m%d_%H%M%S");
    
    string activeBackup = backupName.str() + "_active.txt";
    string completedBackup = backupName.str() + "_completed.txt";
    
    // 备份未完成任务文件
    ifstream src1(ACTIVE_TASKS_FILE, ios::binary);
    ofstream dst1(activeBackup, ios::binary);
    
    if (src1 && dst1) {
        dst1 << src1.rdbuf();
        cout << "未完成任务已备份到: " << activeBackup << endl;
    } else {
        cerr << "未完成任务备份失败" << endl;
    }
    
    // 备份已完成任务文件
    ifstream src2(COMPLETED_TASKS_FILE, ios::binary);
    ofstream dst2(completedBackup, ios::binary);
    
    if (src2 && dst2) {
        dst2 << src2.rdbuf();
        cout << "已完成任务已备份到: " << completedBackup << endl;
    } else {
        cerr << "警告: 已完成任务备份失败" << endl;
    }
    
    return true;
}

// 列出数据文件
void listDataFiles() {
    cout << "\n=== 数据文件列表 ===" << endl;
    
    // 检查未完成任务文件
    ifstream activeFile(ACTIVE_TASKS_FILE);
    if (activeFile.good()) {
        // 获取文件大小
        activeFile.seekg(0, ios::end);
        streampos fileSize = activeFile.tellg();
        activeFile.close();
        
        cout << "✓ 未完成任务文件: " << ACTIVE_TASKS_FILE 
             << " (" << fileSize << " 字节)" << endl;
    } else {
        cout << "✗ 未找到未完成任务文件" << endl;
    }
    
    // 检查已完成任务文件
    ifstream completedFile(COMPLETED_TASKS_FILE);
    if (completedFile.good()) {
        completedFile.seekg(0, ios::end);
        streampos fileSize = completedFile.tellg();
        completedFile.close();
        
        cout << "✓ 已完成任务文件: " << COMPLETED_TASKS_FILE 
             << " (" << fileSize << " 字节)" << endl;
    } else {
        cout << "✗ 未找到已完成任务文件" << endl;
    }
}
bool clearDataFile(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "错误: 无法清空文件 " << filename << endl;
        return false;
    }
    file << "# 任务数据文件 (已清空)" << endl;
    file << "# 格式: id|事项标题|优先级|开始时间|截至时间|是否完成|备注" << endl;
    file.close();
    
    cout << "已清空文件: " << filename << endl;
    return true;
}
