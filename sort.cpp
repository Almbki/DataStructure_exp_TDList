#include "Task.hpp"
#include <utility>
/*指针数组array存排序完的节点指针*/

template <typename fanc>
void QuickSort(Task_data *array[], int length, fanc fanc) // 快速排序并展示
{
    if (length < 2)
        return;

    Task_data *first = array[0], *p = first, *la = array[length - 1];
    while (true)
    {
        while (left != right && comp(*(--right), pivot))
        {
        }
        if (left == right)
            break;
        *left = *right;

        while (left != right && !comp(*(++left), pivot))
        {
        }
        if (left == right)
            break;
        *right = *left;
    }

    *left = pivot;

    // 递归小分区，迭代大分区（防栈溢出）
    if (left - first < last - left)
    {
        my_sort(first, left, comp);
        first = left + 1;
    }
    else
    {
        my_sort(left + 1, last, comp);
        last = left;
    }
}
void Task_Stru::SortBy_ddl()
{
    TNode_elem array[head->length];
    TNode_elem *first = head->first;
    TNode_elem *tail = head->tail;
    while (first == tail)
    {
    }
}

void Task_Stru::SortBy_priority()
{
}