#ifndef COMPLETE_BINARY_TREE
#define COMPLETE_BINARY_TREE

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>

 struct QueueForTree
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



template <typename T>

class ComBinTree
{
private:

       
    struct NodeTree
    {
    T value;
    NodeTree* left;
    NodeTree* right;
    NodeTree(T val) : value(val), left(nullptr), right(nullptr) {}; // Конструктор для инициализации значения
    };

    NodeTree* root{ nullptr };
    QueueForTree <NodeTree*> queue;// хранит указатели на узлы дерева

    void clearingTheQueue();
  

public:

    void push(T item);
    
    void print();
    
    void readingConfiguration(string nameFile);
    
    void writeToConfiguration(string nameFile);
   
    bool isComplete();
    
    bool find(T item);
    
};

#include "../Source/ComBinTree.cpp"

#endif