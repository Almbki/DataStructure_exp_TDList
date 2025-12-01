#if !defined(TASK_H)
#define TASK_H
#include <string>

struct Task
{
    int id;      //标识
    std::string title;
    std::string note;
    int startline;
    int deadline;
    int priority;   //1-10
    bool finished;
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

TList createList();
void InsertList(TList &t, TNode *newNode);
bool DeleteList(TList &t, int id);



#endif // TASK_H
