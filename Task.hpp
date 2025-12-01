#if !defined(TASK_H)
#define TASK_H
#include <string>

struct Task
{
    int id;      //标识
    std::string title;
    std::string note;
    int startline;    //202512011230
    int deadline;
    int priority;   //1-10
    bool finish;
};

typedef struct TNode
{
    Task data;
    TNode *next;

    TNode(const Task &t);

}TNode, *TList;

typedef struct TreeNode
{
    Task data;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode, *TaskTree;




#endif // TASK_H
