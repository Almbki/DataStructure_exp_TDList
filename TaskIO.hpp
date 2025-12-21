#pragma once
#include <string>
#include "Task.hpp"


namespace IO {
    // 输出
    void printTaskHeader();
    void printTaskFooter();
    //void printTask(const TNode_elem* node);
    void printEmpty();
    void printTaskRow(const Task_data &task);
    void printSeparator();
    void printMenu();
    void printOptionMenu(std::string str);

    // 输入
    Task_data inputTask();
    //int inputTaskId();

    int getChoice();
}
