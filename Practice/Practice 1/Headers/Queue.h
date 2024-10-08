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
    NodeQueue* tail{ nullptr }; // Указатель на конец очереди
    int sizeList = 0;

public:
    Queue() = default;
    
    ~Queue() 
    {
        while (head != nullptr) 
        {
            pop_front(); // Освобождаем память при разрушении очереди
        }
    }

    int getSize();

    void push_back(T item);

    T pop_front();
    
    T getFront();
};

#include "../Source/Queue.cpp"

#endif