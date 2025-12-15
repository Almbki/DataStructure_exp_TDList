#include <iostream>
#include <cassert>
#include "Task.hpp"

int main()
{
    std::cout << "开始测试排序功能...\n";

    // 创建任务管理系统
    Task_Stru taskManager;

    // 插入测试数据
    Task_data t1 = {1, "买菜", "去超市买菜", 202512081000, 202512101200, 5, false};
    Task_data t2 = {2, "写报告", "完成实验报告", 202512081300, 202512081500, 8, false};
    Task_data t3 = {3, "健身", "去健身房", 202512081800, 202512122000, 6, false};
    Task_data t4 = {4, "看电影", "观看新电影", 202512091000, 202512091200, 3, false};
    Task_data t5 = {5, "约会", "和朋友约会", 202512101000, 202512111200, 9, false};

    taskManager.InsertNode(t1);
    taskManager.InsertNode(t2);
    taskManager.InsertNode(t3);
    taskManager.InsertNode(t4);
    taskManager.InsertNode(t5);

    std::cout << "原始任务列表:\n";
    taskManager.PrintList();

    std::cout << "\n按截止时间排序:\n";
    taskManager.SortBy_ddl();

    std::cout << "\n按优先级排序:\n";
    taskManager.SortBy_priority();

    // 测试空链表排序
    Task_Stru emptyManager;
    std::cout << "\n测试空链表排序:\n";
    emptyManager.SortBy_ddl();
    emptyManager.SortBy_priority();

    // 测试单节点链表排序
    Task_Stru singleManager;
    Task_data singleTask = {6, "单一任务", "只有一个任务", 202512101000, 202512101200, 7, false};
    singleManager.InsertNode(singleTask);

    std::cout << "\n测试单节点链表排序:\n";
    std::cout << "按截止时间排序:\n";
    singleManager.SortBy_ddl();
    std::cout << "按优先级排序:\n";
    singleManager.SortBy_priority();

    std::cout << "\n所有排序测试完成!\n";

    return 0;
}