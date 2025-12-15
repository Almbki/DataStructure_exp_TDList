// main.cpp
#include "TaskPersistence.hpp"
#include "Task.hpp"
#include <iostream>

int main() {
    std::cout << "=== 任务管理系统 - 简易测试 ===" << std::endl;

    // 创建两个任务管理器：活跃任务 + 已完成任务
    Task_Stru activeTasks;
    Task_Stru completedTasks;

    // 创建持久化对象（使用默认文件名）
    TaskPersistence persistence;

    // === 1. 加载现有数据（如果文件存在）===
    std::cout << "\n[1] 正在加载任务...\n";
    persistence.loadActiveTasks(activeTasks);
    persistence.loadCompletedTasks(completedTasks);

    // === 2. 创建一个新任务 ===
    std::cout << "\n[2] 创建新任务...\n";
    int newId = persistence.getNextAvailableId(activeTasks, completedTasks);
    Task_data newTask = {12,"test","fix the email to get green box",202512011200,202512312359,8,false};
    // Task_data newTask = TaskPersistence::createTask(
    //     "测试任务：GitHub 贡献修复",
    //     "确保邮箱一致，绿格子就会回来！",
    //     202512312359,  // 截止时间：2025-12-31 23:59
    //     8,
    //     false
    // );
    //newTask.id = newId;
    activeTasks.InsertNode(newTask);
    std::cout << "✅ 已添加任务: " << newTask.title << std::endl;

    // === 3. 保存回文件 ===
    std::cout << "\n[3] 正在保存任务到文件...\n";
    persistence.saveActiveTasks(activeTasks);
    persistence.saveCompletedTasks(completedTasks);
    std::cout << "✅ 保存成功！请检查 active_tasks.txt\n";

    // === 4. 验证：打印所有活跃任务 ===
    std::cout << "\n[4] 当前活跃任务列表：\n";
    activeTasks.PrintList();

    std::cout << "\n=== 测试完成 ===\n";
    std::cout << "如果配置正确，本次提交将计入 GitHub 贡献！\n";

    return 0;
}