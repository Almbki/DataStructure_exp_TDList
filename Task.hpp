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
    bool finished;
};

typedef struct TNode
{
    Task data;
    TNode *next;
    TNode *prior;

    TNode(const Task_data &t);

    TNode(const Task &t);

}TNode, *TList;

typedef struct TreeNode
{
    Task data;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode, *TaskTree;


struct TList
{
    int length;      // 链表长度（不计头节点）
    TNode *first;    // 第一个任务节点
    TNode *tail;     // 最后一个任务节点
};

/*
typedef struct TreeNode
{
    Task data;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode, *TaskTree;
*/

TList createList();                              
void InsertList(TList head, TNode *newNode);     
bool DeleteList(TList head, int id);



#endif // TASK_H
