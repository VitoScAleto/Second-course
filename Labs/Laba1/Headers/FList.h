#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <fstream>

using namespace std;

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

    int getSize();
    int GetIndex();
    void push_back(T item);
    void push_front(T item);
    void search_by_value(T item);
    void pop_back();
    void pop_front();
    void delete_by_value(T item);
    void printList();
    void readingConfiguration(string nameFile);
    void writeToConfiguration(string nameFile);
};

    
    int FunDLList();

#include "../Source/FList.cpp"

#endif