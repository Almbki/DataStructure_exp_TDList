#if !defined(TASK_H)
#define TASK_H
#include <string>

struct Task_data // 单个任务结构信息组成
{
    int id; // 标识
    std::string title;
    std::string note;
    long long startline; // 202512011230
    long long deadline;
    int priority; // 1-10
    bool finished;
};

struct TNode_elem // 双向链表元素节点
{
    Task_data task;
    TNode_elem *next;
    TNode_elem *prior;
};

struct TList // 头节点
{
    int length; // 链表长度（不计头节点）
    TNode_elem *first;
    TNode_elem *tail;
};

using TNode_head = TList *;

class Task_Stru
{

private:
    TNode_head head;

public:
    Task_Stru();
    virtual ~Task_Stru();

    TNode_head createList();
    void InsertNode(const Task_data &task);
    bool DeleteNode(int id);
    TNode_elem *findNode(int id);
    bool EditNode(TNode_elem *p);
    void PrintList() const;
    void PrintNode(const TNode_elem *elem_node) const;
    //void SearchNode(int id);
    //void SortBy_ddl();
    //void SortBy_priority();
    TNode_head getHead() const { return head; }
};

#endif // TASK_H
