#ifndef SORT_H
#define SORT_H
#include "Task.hpp"

class sort
{
public:
    sort(/* args */);
    ~sort();

public:
    static void sortBy_deadline(Task_Stru::TNode_head &head);
    static void sortBy_priority();
};

#endif