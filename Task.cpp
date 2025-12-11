#include <iostream>
#include <iomanip>
#include <limits>
#include "Task.hpp"

Task_Stru::Task_Stru() {
    head = new TList{0, nullptr, nullptr};
}

Task_Stru::~Task_Stru() {
    if (!head) return;

    TNode_elem* p = head->first;
    while (p) {
        TNode_elem* next = p->next;
        delete p;
        p = next;
    }
    delete head;
}

TNode_head Task_Stru::createList() {
    
    if (head) {
        TNode_elem* p = head->first;
        while (p) {
            TNode_elem* next = p->next;
            delete p;
            p = next;
        }
        delete head;
    }

    head = new TList{0, nullptr, nullptr};
    return head;
}

void Task_Stru::InsertNode(TNode_elem* newNode) {
    if (!head) createList();

    if (head->first == nullptr) {
        head->first = newNode;
        head->tail = newNode;
        newNode->prior = nullptr;
        newNode->next = nullptr;
        head->length = 1;
        return;
    }

    TNode_elem* p = head->tail;
    p->next = newNode;
    newNode->prior = p;
    newNode->next = nullptr;

    head->tail = newNode;
    head->length++;
}

bool Task_Stru::DeleteNode(int id) {
    if (!head || head->first == nullptr) return false;

    TNode_elem* p = head->first;

    while (p != nullptr) {
        if (p->task.id == id) {

            if (p->prior == nullptr) {         // 删除的是第一个节点
                head->first = p->next;
                if (head->first)
                    head->first->prior = nullptr;
            } else {
                p->prior->next = p->next;
            }

            if (p->next == nullptr) {          // 删除的是最后一个节点
                head->tail = p->prior;
            } else {
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

void Task_Stru::PrintNode(const TNode_elem* elem_node) const {
    //  ID 标题 优先级 截止时间 状态

    if (!elem_node) return;

    std::cout << std::left << std::setw(6)  << elem_node->task.id << "\t";
    std::cout << std::setw(25) << elem_node->task.title << "\t";
    std::cout << std::setw(15) << elem_node->task.priority<< "\t";
    std::cout << std::setw(15) << elem_node->task.deadline<< "\t";
    std::cout << std::setw(10) << (elem_node->task.finished ? "已完成" : "未完成") << "\t";
    std::cout << "\n";
}


void Task_Stru::PrintList() const {
    if (!head || head->first == nullptr) {
        std::cout << "链表为空。\n";
        return;
    }

    std::cout << "------------------------------------------------------------------------\n";
    std::cout 
        << std::left << std::setw(6)  << "ID" << "\t"
        << std::setw(25) << "标题" << "\t"
        << std::setw(15) << "优先级" << "\t"
        << std::setw(15) << "截止时间" << "\t"
        << std::setw(10) << "状态" 
        << "\n";
    std::cout << "------------------------------------------------------------------------\n";

    TNode_elem* p = head->first;
    while (p) {
        PrintNode(p);
        p = p->next;
    }

    std::cout << "------------------------------------------------------------------------\n";
}

TNode_elem* Task_Stru::findNode(int id) {
    TNode_elem* p = head ? head->first : nullptr;


    while (p != nullptr) {
        if (p->task.id == id) {
            return p;
        }
        p = p->next;
    }

    std::cout << "未找到 ID = " << id << " 的任务。\n";
    return nullptr;
}


bool Task_Stru::EditNode(TNode_elem* p) {
    if (!p) return false;  

    bool editing = true;

    while (editing) {
        PrintNode(p);

        std::cout << "请输入数字选择要修改的项：\n"
                  << "1. 标题\n"
                  << "2. 备注\n"
                  << "3. 开始时间\n"
                  << "4. 截止时间\n"
                  << "5. 优先级\n"
                  << "6. 是否完成\n"
                  << "0. 退出修改\n";

        int select = -1;
        std::cin >> select;
        std::cin.ignore();
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区

        switch (select) {
            case 1:
                std::cout << "新的标题：";
                std::cin >> p->task.title;
                //std::getline(std::cin, p->task.title);
                break;
            case 2:
                std::cout << "新的备注：";
                std::cin >> p->task.note;
                //std::getline(std::cin, p->task.note);
                break;
            case 3:
                std::cout << "新的开始时间：";
                std::cin >> p->task.startline;
                break;
            case 4:
                std::cout << "新的截止时间：";
                std::cin >> p->task.deadline;
                break;
            case 5:
                do {
                    std::cout << "新的优先级（1-10）：";
                    std::cin >> p->task.priority;
                } while (p->task.priority < 1 || p->task.priority > 10);
                break;
            case 6:
                do {
                    std::cout << "是否完成（0未完成 / 1已完成）：";
                    std::cin >> p->task.finished;
                } while (p->task.finished != 0 && p->task.finished != 1);
                break;
            case 0:
                editing = false;
                continue;
            default:
                std::cout << "无效选择，请重新输入。\n";
                break;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清理换行符
    }

    return true;
}

