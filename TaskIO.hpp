#pragma once
#include <string>
#include "Task.hpp"


namespace IO {
    // 输出
    void printTaskHeader();
    void printTaskFooter();
    //void printTask(const TNode_elem* node);
    void printEmpty();

    // 额外输出函数
    void printTaskRow(const Task_data &task);
    void printSeparator();

    // 输入
    Task_data inputTask();
    int inputTaskId();
}
