#include <iostream>
#include "Task.hpp"

// 打印链表
void printList(const TList *list){
    TNode *p = list->first;
    while (p != nullptr){
        const Task_data &t = p->task;

        std::cout << "id=" << t.id
                  << ", title=" << t.title
                  << ", note=" << t.note
                  << ", start=" << t.startline
                  << ", deadline=" << t.deadline
                  << ", priority=" << t.priority
                  << ", finished=" << t.finished
                  << std::endl;

        p = p->next;
    }
}

int main(){
    TList *list = createList();

    Task_data t1 = {1, "Task1", "test1", 111, 222, 5, false};
    Task_data t2 = {2, "Task2", "test2", 333, 444, 3, true};
    Task_data t3 = {3, "Task3", "test3", 555, 666, 8, false};

    TNode *n1 = new TNode(t1);
    TNode *n2 = new TNode(t2);
    TNode *n3 = new TNode(t3);

    InsertNode(list, n1);
    InsertNode(list, n2);
    InsertNode(list, n3);

    std::cout << "=== After Insert ===" << std::endl;
    printList(list);

    DeleteNode(list, 2);

    std::cout << "\n=== After Delete id=2 ===" << std::endl;
    printList(list);

    return 0;
}
