#include "Task.hpp"

TNode::TNode(const Task_data &t) : task(t), next(nullptr), prior(nullptr) {}

TList createList(){
    THead blank = {0,nullptr,nullptr};
    THead head = new THead(blank);
    head->next = nullptr;
    head->prior = nullptr;
    return head;
}

void InsertNode(TList head, TNode *newNode){
    TNode *p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }

    p->next = newNode;
    newNode->prior = p;
    newNode->next = nullptr;

}

TNode *InsertList(TNode *newNode, TNode *tail){


}