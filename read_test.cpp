#include "read.h"
#include <iostream>

int main() {
    // 创建任务管理器（未完成任务）
    Task_Stru activeTasks;
    
    // 创建任务管理器（已完成任务）
    Task_Stru completedTasks;
    
    cout << "=== 测试B组IO模块 ===" << endl;
    
    // 1. 加载数据
    cout << "\n1. 加载未完成任务..." << endl;
    if (loadDataFromFile(activeTasks, false, "active_tasks.txt")) {
        cout << "加载成功!" << endl;
    } else {
        cout << "创建新的未完成任务文件" << endl;
    }
    
    cout << "\n2. 加载已完成任务..." << endl;
    if (loadDataFromFile(completedTasks, true, "completed_tasks.txt")) {
        cout << "加载成功!" << endl;
    } else {
        cout << "创建新的已完成任务文件" << endl;
    }
    
    // 2. 显示文件列表
    cout << "\n3. 数据文件列表:" << endl;
    listDataFiles();
    
    // 3. 创建新任务
    cout << "\n4. 创建新任务..." << endl;
    int nextId = getNextAvailableId(activeTasks, false);
    
    cout << "请输入任务标题: ";
    string title;
    getline(cin, title);
    
    cout << "请输入任务备注 (可选): ";
    string note;
    getline(cin, note);
    
    cout << "请输入截止时间 (YYYYMMDDHHMM, 0表示无截止时间): ";
    string deadlineStr;
    getline(cin, deadlineStr);
    int deadline = 0;
    if (deadlineStr != "0") {
        deadline = stoi(deadlineStr);
    }
    
    cout << "请输入优先级 (1-10, 默认为5): ";
    string priorityStr;
    getline(cin, priorityStr);
    int priority = priorityStr.empty() ? 5 : stoi(priorityStr);
    
    // 创建任务
    Task_data newTask = createTask(title, note, deadline, priority, false);
    newTask.id = nextId;
    
    // 创建节点并插入链表
    TNode_elem* newNode = new TNode_elem;
    newNode->task = newTask;
    newNode->next = nullptr;
    newNode->prior = nullptr;
    
    activeTasks.InsertNode(newNode);
    
    cout << "\n新任务已创建:" << endl;
    cout << "  ID: " << newTask.id << endl;
    cout << "  标题: " << newTask.title << endl;
    cout << "  创建时间: " << dateTimeToString(newTask.startline) << endl;
    cout << "  截止时间: " << (newTask.deadline == 0 ? "无" : dateTimeToString(newTask.deadline)) << endl;
    cout << "  备注: " << (newTask.note.empty() ? "无" : newTask.note) << endl;
    cout << "  优先级: " << newTask.priority << endl;
    cout << "  状态: " << (newTask.finished ? "已完成" : "未完成") << endl;
    
    // 4. 保存数据
    cout << "\n5. 保存数据..." << endl;
    if (saveDataToFile(activeTasks, false, "active_tasks.txt")) {
        cout << "未完成任务保存成功!" << endl;
    }
    
    if (saveDataToFile(completedTasks, true, "completed_tasks.txt")) {
        cout << "已完成任务保存成功!" << endl;
    }
    
    // 5. 备份数据
    cout << "\n6. 备份数据..." << endl;
    backupDataFiles();
    
    // 6. 显示所有任务
    cout << "\n7. 当前未完成任务列表:" << endl;
    activeTasks.PrintList();
    
    cout << "\n8. 当前已完成任务列表:" << endl;
    completedTasks.PrintList();
    
    cout << "\n=== 测试完成 ===" << endl;
    
    return 0;
}