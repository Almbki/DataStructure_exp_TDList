#if !defined(TASK_H)
#define TASK_H
#include <string>

struct Task
{
    int id; // 标识
    std::string title;
    std::string note;
    int create_time; // 202512011205
    int deadline;
    int priority; // 1-10
    bool finish;
};

struct TNode
{
    Task data;
    TNode *next;

    TNode(const Task &t);
};

#endif // TASK_H
