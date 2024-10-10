#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "Headers.h"

template <typename T>

struct LinkedList
{
private:
    

    struct Node
    {
        T value;
        Node* next;
        Node(T val) : value(val), next(nullptr) {}; // Конструктор для инициализации значения
    };

    Node* head{ nullptr };

    int sizeList = 0;
    int index = 0;

    bool isValidValue(T item);
    
public:
    T getHead();
    int getSize();
    int GetIndex();
    void push_back(T item);
    void push_front(T item);
    int search_by_value(T item);
    void pop_back();
    void pop_front();
    void delete_by_value(T item);
    void printList();
    void Replace_by_index(int indexValue, T newValue);
};



#include "../Source/FList.cpp"


#endif