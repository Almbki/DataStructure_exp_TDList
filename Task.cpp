#include <iostream>
#include <iomanip>
#include "Task.hpp"

Task_Stru::Task_Stru(){head = nullptr;}

Task_Stru::~Task_Stru(){
    
    if (!head) return ;

    TNode_elem *p = head->first;
    while (p)
    {
        TNode_elem *next = p->next;
        delete p;
        p = next;
    }
    delete head;

}

Task_Stru::TNode_head Task_Stru::createList(){
    head = new TList{0, nullptr, nullptr};
    return head;
}

void Task_Stru::InsertNode(TNode_head head, TNode_elem *newNode){
    if (head->first == nullptr)
    {
        head->first = newNode;
        head->tail = newNode;
        head->length = 1;
        newNode->prior = nullptr;

        return ;
    }

    TNode_elem *p = head->tail;
    p->next = newNode;
    newNode->prior = p;
    head->tail = newNode;
    head->length++;

}

bool Task_Stru::DeleteNode(TNode_head head, int id){
    if (head->first = nullptr) return false;

    TNode_elem *p = head->first;
    while (p != nullptr)
    {
        if (p->task.id == id)
        {
            if (p->prior == nullptr)        //找到的节点没有前驱
            {
                head->first = p->next;
                if (head->first)
                {
                    head->first->prior = nullptr;
                }
            }
            else
            {
                p->prior->next = p->next;
            }

            if (p->next == nullptr)         //找到的节点没有后继
            {
                head->tail = p->prior;
                if (head->tail)
                {
                    head->tail->next = nullptr;
                }
            }
            else
            {
                p->next->prior = p->prior;
            }

            delete p;
            head->length--;
            return true;
        }
        p = p->next;
    }
    return false;    
}

void Task_Stru::PrintNode(const TNode_elem *elem_node){
{
    if (!elem_node)
    {
        std::cout << "（空节点）\n";
        return;
    }

    std::cout << "----------------------------------------\n";
    std::cout << "任务详情\n";
    std::cout << "----------------------------------------\n";

    std::cout << std::left << std::setw(10) << "ID:" 
              << elem_node->task.id << "\n";

    std::cout << std::left << std::setw(10) << "标题:" 
              << elem_node->task.title << "\n";

    std::cout << std::left << std::setw(10) << "备注:" 
              << elem_node->task.note << "\n";

    std::cout << std::left << std::setw(10) << "开始时间:" 
              << elem_node->task.startline << "\n";

    std::cout << std::left << std::setw(10) << "截止时间:" 
              << elem_node->task.deadline << "\n";

    std::cout << std::left << std::setw(10) << "优先级:" 
              << elem_node->task.priority << "\n";

    std::cout << std::left << std::setw(10) << "状态:" 
              << (elem_node->task.finished ? "已完成" : "未完成") << "\n";

    std::cout << "----------------------------------------\n\n";
}
};


bool Task_Stru::EditNode(TNode_head head, int id){
    
    TNode_elem *p = head->first;
    
    while (p != nullptr)
    {
        if (p->task.id == id)
        {
            PrintNode(p);
            int select;

            while (select)
            {
                std::cout << "请输入数字选择要修改的项：\n"
                          << "1. 标题\n"
                          << "2. 备注\n"
                          << "3. 开始时间\n"
                          << "4. 截止时间\n"
                          << "5. 优先级\n"
                          << "6. 是否完成\n"
                          << "0. 退出修改\n";
                std::cin >> select;
                switch (select)
                {
                case 1:
                    std::cout << "请输入新的标题：";
                    std::cin >> p->task.title;
                    break;
                case 2:
                    std::cout << "请输入新的备注：";
                    std::cin >> p->task.note;
                    break;
                case 3:
                    std::cout << "请输入新的开始时间（格式：YYYYMMDDHHMM）：";
                    std::cin >> p->task.startline;
                    break;
                case 4:
                    std::cout << "请输入新的截止时间（格式：YYYYMMDDHHMM）：";
                    std::cin >> p->task.deadline;
                    break;
                case 5:
                    std::cout << "请输入新的优先级（1-10）：";
                    std::cin >> p->task.priority;
                    break;
                case 6:
                    std::cout << "请输入是否完成（0表示未完成，1表示已完成）：";
                    std::cin >> p->task.finished;
                case 0:
                    return true;
                default:
                    std::cout << "无效选择，请重新输入。\n";
                    break;
                }
            }
            
            
        }
        p = p->next;
    }
    std::cout << "未找到ID为 " << id << " 的任务。\n";
    return false;
}

