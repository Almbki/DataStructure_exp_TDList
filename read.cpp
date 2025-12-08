#include "read.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
// 去空格
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}
// 字符串分割
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}
//ddl是否有效
bool validateDeadline(const string& deadlineStr) {
    if (deadlineStr.length() != 12) return false;
    for (char c : deadlineStr) {
        if (!isdigit(c)) return false;
    }
    return true;
}
TList* loadData(const string& filename) {
    ifstream file(filename);
    TList* allList = createList();
    if (!file.is_open()) {
        cout << "注意: 文件不存在，将创建新文件" << endl;
        return allList;
    }
    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (trim(line).empty() || line[0] == '#') continue;
        vector<string> fields = split(line, DELIMITER);
        if (fields.size() < 6) {
            cerr << "警告: 第" << lineNum << "行格式错误" << endl;
            continue;
        }
        Task_data task;
        try {
            task.id = stoi(fields[0]);
            task.title = fields[1];
            task.priority = stoi(fields[2]);
            task.deadline = stoi(fields[3]);
            task.finished = (fields[4] == "1");
            task.note = fields[5];
            task.startline = 0;
            if (task.deadline != 0 && !validateDeadline(fields[3])) {
                cerr << "警告: 第" << lineNum << "行截止日期格式错误" << endl;
                task.deadline = 0;
            }
        } catch (...) {
            cerr << "警告: 第" << lineNum << "行数据格式错误" << endl;
            continue;
        }
        TNode* newNode = new TNode(task);
        InsertNode(allList, newNode);
    }
    file.close();
    cout << "从文件加载了 " << allList->length << " 个任务" << endl;
    return allList;
}
bool saveData(TList* taskList, const string& filename) {
    if (!taskList || taskList->length == 0) {
        cout << "任务列表为空，不保存" << endl;
        return false;
    }
    
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "错误: 无法创建/打开文件" << endl;
        return false;
    }
    file << "任务数据文件" << endl;
    file << "格式: id|title|priority|deadline|state|description" << endl;
    file << "state: 0=未完成, 1=已完成" << endl;
    file << "deadline: YYYYMMDDHHMM 或 0(无截止时间)" << endl;
    file << endl;
    TNode* current = taskList->first;
    int savedCount = 0;
    
    while (current != nullptr) {
        const Task_data& task = current->task;
        file << task.id << DELIMITER
             << task.title << DELIMITER
             << task.priority << DELIMITER
             << task.deadline << DELIMITER
             << (task.finished ? "1" : "0") << DELIMITER
             << task.note << endl;
        
        current = current->next;
        savedCount++;
    }
    
    file.close();
    cout << "成功保存 " << savedCount << " 个任务到文件" << endl;
    return true;
}
// 测试用main
int main() {
    // 测试loadData
    TList* allTasks = loadData("tasks.txt");
    
    // 简单打印任务数量
    cout << "总共 " << allTasks->length << " 个任务" << endl;
    
    // 测试saveData
    if (saveData(allTasks, "tasks_backup.txt")) {
        cout << "保存成功！" << endl;
    }
    
    return 0;
}