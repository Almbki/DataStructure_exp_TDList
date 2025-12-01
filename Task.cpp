#include "Task.hpp"

TNode::TNode(const Task &t){
    data = t;
    next = nullptr;
}