#if !defined(TASK_H)
#define TASK_H
#include <string>

struct task
{
    int id;      //标识
    std::string title;
    std::string note;
    int month, day, hour, minute;
    int priority;   //1-10
    bool finish;
};

struct TNode
{
    task data;
    TNode *next;

    TNode(const task &t);
};



#endif // TASK_H
