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
        Node(T val) : value(val), next(nullptr) {}
    };

    Node* head{ nullptr };
    int sizeList = 0;

public:
    ~LinkedList();
    T& operator[](int index);
    T getHead();
    int getSize();
    void push_back(T item);
    void push_front(T item);
    bool search_by_value_bool(T item);
    void pop_back();
    int search_by_value_return_index(T item); 
    void pop_front();
    void delete_by_value(T item);
    void printList();
    T Get_by_index(int indexValue);
    void delete_by_index(int index);
};



#include "../Source/FList.cpp"


#endif