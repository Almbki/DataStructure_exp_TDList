#include "read.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    Task_Stru activeTasks;
    Task_Stru completedTasks;
    cout << "加载未完成任务..." << endl;
    loadDataFromFile(activeTasks, false, ACTIVE_TASKS_FILE);

    cout << "加载已完成任务..." << endl;
    loadDataFromFile(completedTasks, true, COMPLETED_TASKS_FILE);
    cout << "\n=== 当前未完成任务 ===\n";
    activeTasks.PrintList();

    cout << "\n=== 当前已完成任务 ===\n";
    completedTasks.PrintList();
    cout << "\n创建一个新任务用于测试...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string title, note, ddlStr;
    int priority;
    cout << "任务标题: ";
    getline(cin, title);

    cout << "任务备注: ";
    getline(cin, note);

    cout << "截止时间 (YYYYMMDDHHMM，0 表示无): ";
    getline(cin, ddlStr);

    cout << "优先级 (1-10): ";
    cin >> priority;

    int deadline = (ddlStr == "0") ? 0 : stoi(ddlStr);

    Task_data t = createTask(title, note, deadline, priority, false);
    //t.id = getNextAvailableId(activeTasks);

    activeTasks.InsertNode(t);
    cout << "\n保存数据到文件...\n";
    saveDataToFile(activeTasks, false, ACTIVE_TASKS_FILE);
    saveDataToFile(completedTasks, true, COMPLETED_TASKS_FILE);
    cout << "\n=== 保存后的未完成任务 ===\n";
    activeTasks.PrintList();

    cout << "\n=== 保存后的已完成任务 ===\n";
    completedTasks.PrintList();

    cout << "\n测试完成。\n";
    return 0;
}
