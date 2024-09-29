#include <iostream>

using namespace std;

template <typename T>

struct Node
{
    T value;
    Node* next;
    Node* prevToNode;
    Node(T val) : value(val), next(nullptr), prevToNode(nullptr) {}; // Конструктор для инициализации значения
};

template <typename T>

struct DLinkedList
{
private:

    Node<T>* head{ nullptr };
    Node<T>* tail{ nullptr };

    int sizeList = 0;
    int index = 0;

public:
    void getSize()
    {
        cout << sizeList << endl;
    }
    void push_back(T item)
    {
        Node<T>* currentPtr = new Node<T>(item);
        if (head == nullptr)
        {
            head = currentPtr;
            sizeList++;
        }
        else if (tail == nullptr)
        {
            tail = currentPtr;
            head->next = tail;
            tail->prevToNode = head;
            sizeList++;
        }
        else
        {
            Node<T>* prevPtr = tail;
            tail = currentPtr;
            prevPtr->next = tail;
            tail->prevToNode = prevPtr;
            sizeList++;
        }
    }  
    
    void push_front(T item)
    {
        Node<T>* currentPtr = new Node<T>(item);

        if (tail == nullptr)
        {
            tail = currentPtr;
            sizeList++;
        }
        else if (head == nullptr)
        {
            head = currentPtr;
            head->next = tail;
            tail->prevToNode = head;
            sizeList++;
        }
        else
        {
            Node<T>* prevPtr = head;
            head = currentPtr;
            prevPtr->prevToNode = head;
            head->next = prevPtr;
            sizeList++;
        }
    }

    void pop_back()
    {
        if (sizeList == 0)
        {
            cerr << "Error. Empty list" << endl;
            sizeList--;
            return;
        }
        if (head == nullptr)
        {
            delete tail;
            sizeList--;
            return;
        }
        if (tail == nullptr)
        {
            delete head;
            sizeList--;
            return;
        }
        if (sizeList == 2)
        {
            delete tail;
            sizeList--;
            return;

        }
        else
        {
            Node<T>* currentPtr = head;
            Node<T>* prevPtr = nullptr;

            while (currentPtr->next == nullptr)
            {
                currentPtr = currentPtr->next;
            }
            prevPtr = currentPtr->prevToNode;

            delete tail;

            tail = prevPtr;
        }
    }

    void printListFront()
    {
        Node<T>* currentPtr = head;
        while (currentPtr != nullptr)
        {
            cout << currentPtr->value <<" ";
            currentPtr = currentPtr->next;
        }
        cout << endl;
    }
    void printListBack()
    {
        Node<T>* currentPtr = tail;
        while (currentPtr != nullptr)
        {
            cout << currentPtr->value << " ";
            currentPtr = currentPtr->prevToNode;
        }
        cout << endl;
    }
};



int main()
{
    DLinkedList<int> DList;
    DList.push_front(5);
    DList.printListFront();
    DList.push_front(6);
    DList.printListFront();
    DList.push_front(7);
    DList.printListFront();
    DList.push_front(8);
    DList.printListFront();
    DList.push_front(9);
    DList.printListFront();
    DList.push_front(10);
    DList.printListFront();
    return 0;
}