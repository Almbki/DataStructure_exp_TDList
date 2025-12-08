#include "read.h"
#include <iostream>
int main() {
    TList* allTasks = loadData("tasks.txt");
    
    // 简单打印任务数量
    cout << "总共 " << allTasks->length << " 个任务" << endl;
    
    // 测试saveData
    if (saveData(allTasks, "tasks_backup.txt")) {
        cout << "保存成功！" << endl;
    }
    
    return 0;
}