#if !defined(TASK_H)
#define TASK_H
#include <string>

struct Task_data
{
    int id;      //标识
    std::string title;
    std::string note;
    int startline;    //202512011230
    int deadline;
    int priority;   //1-10
    bool finished;
};


struct TNode
{
    Task_data task;
    TNode *next;
    TNode *prior;

    TNode(const Task_data &t);

};

struct TList
{
    int length;      // 链表长度（不计头节点）
    TNode *first;   
    TNode *tail;     
};

/*
typedef struct TreeNode
{
    Task data;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode, *TaskTree;
*/

TList *createList();                              
void InsertNode(TList *head, TNode *newNode);     
bool DeleteNode(TList *head, int id);



#endif // TASK_H
