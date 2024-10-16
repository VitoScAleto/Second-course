#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>

struct Stack
{
private:

    struct NodeStack
    {
        T value;
        NodeStack* next;
        NodeStack(T val) : value(val), next(nullptr) {}; // Конструктор для инициализации значения
    };

    NodeStack* head{ nullptr };

    int sizeList = 0;
    bool isValidValue(T item);
    
public:

    int getSize();
    void push_front(T item);
    void pop_front();
    void printStack();
    void readingConfiguration(string nameFile);
    void writeToConfiguration(string nameFile);
};


    

#include "../Source/stack.cpp"

#endif