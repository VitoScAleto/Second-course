#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>

struct DLinkedList
{
private:


    struct NodeDLL
    {
        T value;
        NodeDLL* next;
        NodeDLL* prevToNode;
        NodeDLL(T val) : value(val), next(nullptr), prevToNode(nullptr) {}; // Constructor for initializing value
    };

    NodeDLL* head{ nullptr };
    NodeDLL* tail{ nullptr };

    int sizeList = 0;
    int index = 0;
    
    bool isValidValue(T item);

public:

    DLinkedList();
    void getSize();
    void push_back(T item);
    void push_front(T item);
    void pop_back();
    void pop_front();
    void delete_by_value(T item);
    void printList();
    void search_by_value(T item);
    void readingConfiguration(string nameFile);
    void writeToConfiguration(string nameFile);
};


#include "../Source/DLList.cpp"

#endif