#ifndef QUEUE_H
#define QUEUE_H

#include "Headers.h"

template <typename T>

 struct Queue
{
private:

    struct NodeQueue
    {   
        T value;
        NodeQueue* next;
        NodeQueue(T val) : value(val), next(nullptr) {}; // Конструктор для инициализации значения
    };

    NodeQueue* head{ nullptr };
    int sizeList = 0;

public:
    int getSize();
    void push_front(T item);
    T getFront();
    void pop_back();
};

#include "../Source/Queue.cpp"

#endif