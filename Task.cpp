#include "Task.hpp"

TNode::TNode(const Task_data &t) : task(t), next(nullptr), prior(nullptr) {}

TList *createList(){
    TList *head = new TList;
    head->length = 0;
    head->first = nullptr;
    head->tail = nullptr;
    return head;
}

void InsertNode(TList *head, TNode *newNode){
    if (head->first == nullptr){
        head->first = newNode;
        head->tail = newNode;
        head->length = 1;
        return;
    }

    TNode *p = head->tail;
    p->next = newNode;
    newNode->prior = p;
    head->tail = newNode;
    head->length++;

}

TNode *InsertList(TNode *newNode, TNode *tail){


}
