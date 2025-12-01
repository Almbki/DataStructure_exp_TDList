#include "Task.hpp"

TNode::TNode(const Task &t){
    this->data = t;
    this->next = nullptr;
}



TList createList(){
    return nullptr;
}

void InsertList(TList &task, const Task &newNode){
    TNode *node = new TNode(newNode);

    if (task = nullptr)
    {
        task = node;
        return ;
    }

    TNode *p = task;
    while (p->next != nullptr) 
    {
        p = p->next;
    }
    p->next = node;
}

bool DeleteList(TList &task, int id){
    if (task = nullptr) return false;
    if(task->data.id == id){
        TNode * tmp = task;
        task = task->next;
        delete tmp;
        return true;
    }

    TNode *p = task;
    while (p->next != nullptr && p->next->data.id != id)
        p = p->next;
    if(p->next == nullptr) return false;

    TNode *tmp = p->next;
    p->next = tmp->next;
    delete tmp;
    return true;   
}
