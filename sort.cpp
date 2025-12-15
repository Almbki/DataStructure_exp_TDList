#include "Task.hpp"
/*指针数组array存排序完的节点指针*/

template <typename fanc>
void QuickSort(Task_data array[], int length, fanc fanc) // 快速排序并展示
{
    if (length < 2)
        return;
    int left = 0, right = length - 1;
    while (left < right)
    {
        while (left < right && fanc(array[left], array[right]))
            left++;
        while (left < right && !fanc(array[left], array[right]))
            right--;
        std::swap(array[left], array[right]);
    }
    QuickSort(array, left, fanc);
    QuickSort(array + left + 1, length - 1 - left, fanc);
}
void Task_Stru::SortBy_ddl()
{
    Task_data array[head->length];
    TNode_elem *p = head->first;
    for (auto &i : array)
    {
        i = p->task;
        p = p->next;
    }

    QuickSort(array, head->length, [](Task_data a, Task_data b)
              { return a.deadline < b.deadline; });
}

void Task_Stru::SortBy_priority()
{
    Task_data array[head->length];
    TNode_elem *p = head->first;
    for (auto &i : array)
    {
        i = p->task;
        p = p->next;
    }

    QuickSort(array, head->length, [](Task_data a, Task_data b)
              { return a.priority > b.priority; });
}