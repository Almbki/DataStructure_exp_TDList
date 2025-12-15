#include <iostream>
#include "Task.hpp"

int main() {
    Task_Stru taskManager;

    // ===== 插入节点 =====
    Task_data t1 = {1, "买菜", "去超市买菜", 202512081000, 202512081200, 5, false};
    Task_data t2 = {2, "写报告", "完成实验报告", 202512081300, 202512081500, 8, false};
    Task_data t3 = {3, "健身", "去健身房", 202512081800, 202512082000, 6, false};

    taskManager.InsertNode(t1);
    taskManager.InsertNode(t2);
    taskManager.InsertNode(t3);

    std::cout << "插入后的任务列表：\n";
    taskManager.PrintList();

    // ===== 查找节点 =====
    std::cout << "\n查找ID=2的任务：\n";
    taskManager.printNodeById(2);

    // ===== 编辑节点 =====
    std::cout << "\n编辑ID=2的任务：\n";
    if (taskManager.EditNode(2)) {
        std::cout << "编辑完成后的任务：\n";
        taskManager.printNodeById(2);
    }

    // ===== 删除节点 =====
    std::cout << "\n删除ID=1的任务：\n";
    if (taskManager.DeleteNode(1)) {
        std::cout << "删除成功，当前任务列表：\n";
        taskManager.PrintList();
    }

    // ===== 删除不存在的节点 =====
    std::cout << "\n尝试删除ID=100的任务：\n";
    if (!taskManager.DeleteNode(100)) {
        std::cout << "任务ID=100不存在。\n";
    }

    return 0;
}
