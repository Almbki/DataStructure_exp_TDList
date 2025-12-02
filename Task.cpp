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

bool DeleteNode(TList *head, int id){
    TNode *p = head->first;;
    while (p != nullptr){
        if (p->task.id == id){      
            if (p->prior)
                p->prior->next = p->next;
            else
            {
                head->first = p->next;
                if (head->first)        //第一个元素的前驱指空
                    head->first->prior = nullptr;
            }
            if (p->next)
                p->next->prior = p->prior;
            else
            {
                head->tail = p->prior;
                if (head->tail)         //最后一个元素的后继指空
                    head->tail->next = nullptr;
            }
        
            delete p;
            head->length--;
            return true;
        }
        p = p->next;
    }
    return false;
}
    
