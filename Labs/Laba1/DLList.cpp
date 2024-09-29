
#include <iostream>

using namespace std;

template <typename T>

struct Node
{
    T value;
    Node* next;
    Node* prev;
    Node(T val) : value(val), next(nullptr), prev(nullptr) {}; // Конструктор для инициализации значения
};

template <typename T>

struct DLinkedList
{
private:

    Node<T>* head{ nullptr };
    Node<T>* tail{nullptr};
    int sizeList = 0;
    int index = 0;

public:
   
};


int main()
{
  
   
    return 0;
}