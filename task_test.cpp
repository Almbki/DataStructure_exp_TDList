#include <iostream>
#include "Task.hpp"

int main() {
    Task_Stru taskManager;

    // ===== 插入节点 =====
    TNode_elem* t1 = new TNode_elem{{1, "买菜", "去超市买菜", 202512081000, 202512081200, 5, false}, nullptr, nullptr};
    TNode_elem* t2 = new TNode_elem{{2, "写报告", "完成实验报告", 202512081300, 202512081500, 8, false}, nullptr, nullptr};
    TNode_elem* t3 = new TNode_elem{{3, "健身", "去健身房", 202512081800, 202512082000, 6, false}, nullptr, nullptr};

    taskManager.InsertNode(t1);
    taskManager.InsertNode(t2);
    taskManager.InsertNode(t3);

    std::cout << "插入后的任务列表：\n";
    taskManager.PrintList();

    // ===== 查找节点 =====
    std::cout << "\n查找ID=2的任务：\n";
    TNode_elem* node = taskManager.findNode(2);
    if (node) taskManager.PrintNode(node);

    // ===== 编辑节点 =====
    std::cout << "\n编辑ID=2的任务：\n";
    if (taskManager.EditNode(node)) {
        std::cout << "编辑完成后的任务：\n";
        taskManager.PrintNode(node);
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
