#include <iostream>

using namespace std;

template <typename T>

struct Node
{
    T value;
    Node* next;
    Node(T val) : value(val), next(nullptr) {}; // Конструктор для инициализации значения
};

template <typename T>

class LinkedList
{
private:
    Node<T>* head{ nullptr };

public:

    void InsertToBack(T item)
    {
        if (head == nullptr)
        {
            head = new Node<T>(item);
        }
        else
        {
            Node<T>* current = head;
            while (current ->next != nullptr)// бегаем по списку пока не наткнемся на конец
            {
                current = current->next;
            }
            current->next = new Node<T>(item);
        }
    }


};


int main()
{
   
  
    return 0;
}