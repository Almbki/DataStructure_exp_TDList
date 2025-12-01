#ifndef SORT_H
#define SORT_H
#include "task.hpp"

class sort
{
private:
    /* data */
public:
    void bubble_sort(auto *&fist, auto *&las);
    // void quick_sort();
    void sortBy_deadline(Task *&fist, Task *&las);
    void sortBy_priority();
    // void sortOptimal();
};
#endif