#include "Task.hpp"
#include "TaskIO.hpp"
/*指针数组array存排序完的节点指针*/

template <typename fun>
void QuickSort(TNode_elem *array[], int length, fun func) // 快速排序并展示
{
    if (length < 2)
        return;
    int left = 0, right = length - 1;
    // while (left < right)
    // {
    //     while (left < right && func(array[left], array[right]))
    //         left++;
    //     while (left < right && !func(array[left], array[right]))
    //         right--;
    //     std::swap(array[left], array[right]);
    // }
    // QuickSort(array, left, func);
    // QuickSort(array + left + 1, length - 1 - left, fanc);
    TNode_elem *pivot = array[(left + right) / 2];

    while (left <= right)
    {
        while (func(array[left], pivot))
            left++;
        while (func(pivot, array[right]))
            right--;

        if (left <= right)
        {
            std::swap(array[left], array[right]);
            left++;
            right--;
        }
    }

    QuickSort(array, right + 1, func);
    QuickSort(array + left, length - left, func);
}
void Task_Stru::SortBy_ddl()
{
    TNode_elem *array[head->length];
    TNode_elem *p = head->first;
    for (auto &i : array)
    {
        i = p;
        p = p->next;
    }

    QuickSort(array, head->length, [](TNode_elem *a, TNode_elem *b)
              { return a->task.deadline < b->task.deadline; });
    for (auto i : array)
    {
        // Task_Stru::PrintNode(i);
        IO::printTaskRow(i->task);
    }
}

void Task_Stru::SortBy_priority()
{
    TNode_elem *array[head->length];
    TNode_elem *p = head->first;
    for (auto &i : array)
    {
        i = p;
        p = p->next;
    }

    QuickSort(array, head->length, [](TNode_elem *a, TNode_elem *b)
              { return a->task.priority > b->task.priority; });
    for (auto i : array)
    {
        // Task_Stru::PrintNode(i);
        IO::printTaskRow(i->task);
    }
}