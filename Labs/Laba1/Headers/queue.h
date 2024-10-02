#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

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

    bool isValidValue(T item);

public:

    int getSize();
    void push_front(T item);
    void pop_back();
    void printQueue();
    void readingConfiguration(string nameFile);
    void writeToConfiguration(string nameFile);
};

    #include "../Source/queue.cpp"

#endif