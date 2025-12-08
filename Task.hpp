#if !defined(TASK_H)
#define TASK_H
#include <string>

class Task_Stru
{

public:

    struct Task_data    //单个任务结构信息组成
    {
        int id;      //标识
        std::string title;
        std::string note;
        int startline;    //202512011230
        int deadline;
        int priority;   //1-10
        bool finished;
    };

    struct TNode_elem        //双向链表元素节点
    {
        Task_data task;
        TNode_elem *next;
        TNode_elem *prior;
    };

    struct TList        //头节点
    {
        int length;      // 链表长度（不计头节点）
        TNode_elem *first;   
        TNode_elem *tail;     
    };

    using TNode_head = TList*;

private:

    TNode_head head;

public:

    Task_Stru();
    virtual ~Task_Stru();

    virtual TNode_head createList();                              
    virtual void InsertNode(TNode_head head, TNode_elem *newNode);     
    virtual bool DeleteNode(TNode_head head, int id);
    virtual bool EditNode(TNode_head head, int id);
    virtual void PrintList(const TNode_head head);
    virtual void PrintNode(const TNode_elem *elem_node);
    
};


#endif // TASK_H
