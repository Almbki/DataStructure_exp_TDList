#include "read.h"    
#include "Task.hpp" 
#include "TaskIO.hpp" 
#include <iostream>
using namespace std;

int main() {
    Task_Stru taskManager;
    std::cout << "\n[1] 从文件加载数据...\n";
    if (IO_File::loadData(taskManager, "tasks.txt")) {
        std::cout << "✅ 数据加载成功\n";
    } else {
        std::cout << "⚠️文件不存在或为空，将创建新文件\n";
    }
    std::cout << "\n[2] 当前任务列表：\n";
    taskManager.PrintList();
    std::cout << "\n[3] 添加测试任务...\n";
    cout << "输入任务id: ";
    int id;
    string title;
    string note;
    long long starttime;
    long long deadline;
    int priority;
    bool finshed;
    cin >> id;
    cout << "输入任务标题: ";
    cin >> title;
    cout << "输入任务备注: ";
    cin >> note;
    cout << "输入起始时间YYYYMMDDHHMM: ";
    cin >> starttime;
    cout << "输入截止时间YYYYMMDDHHMM: ";
    cin >> deadline;
    cout << "输入优先度0-10: ";
    cin >> priority;
    Task_data testTask = {id, title, note, starttime, deadline, priority, false}; //默认没完成是false
    taskManager.InsertNode(testTask);
    std::cout << "✅ 测试任务已添加\n";
    
    std::cout << "\n[4] 添加后的任务列表：\n";
    taskManager.PrintList();
    std::cout << "\n[5] 保存数据到文件...\n";
    if (IO_File::saveData(taskManager, "tasks.txt")) {
        std::cout << "✅ 数据保存成功！\n";
        std::cout << "   请检查 tasks.txt 文件内容\n";
    } else {
        std::cout << "❌ 保存失败！\n";
    }
    std::cout << "\n[6] 验证：重新加载数据...\n";
    Task_Stru newManager;
    if (IO_File::loadData(newManager, "tasks.txt")) {
        std::cout << "✅ 验证加载成功\n";
        std::cout << "\n重新加载后的任务列表：\n";
        newManager.PrintList();
    }
    return 0;
}
