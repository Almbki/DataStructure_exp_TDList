#include <iostream>
#include "Task.hpp"
#include "SORT.hpp"

int main()
{
    TList *list = createList();
    Task_Stru ts;
    // sort s;
    // ts.sortBy_deadline(list->first);

    Task_data t1 = {1, "Task1", "test1", 111, 222, 5, false};
    Task_data t2 = {2, "Task2", "test2", 333, 444, 3, true};
    Task_data t3 = {3, "Task3", "test3", 555, 666, 8, false};

    TNode *n1 = new TNode(t1);
    TNode *n2 = new TNode(t2);
    TNode *n3 = new TNode(t3);

    InsertNode(list, n1);
    InsertNode(list, n2);
    InsertNode(list, n3);
    std::cout << "=== After Insert ===" << std::endl;
    printList(list);

    DeleteNode(list, 2);

    std::cout << "\n=== After Delete id=2 ===" << std::endl;
    printList(list);

    return 0;
}
