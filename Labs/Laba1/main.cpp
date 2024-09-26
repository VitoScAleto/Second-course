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

struct LinkedList
{
private:

    Node<T>* head{ nullptr };
    int quantity = 0;
    int index = 0;

public:
    int GetQuantity()
    {
        return quantity;
    }
    int GetIndex()
    {
        return index;
    }
    void InsertToBack(T item)
    {
        if (head == nullptr)
        {
            head = new Node<T>(item);
            quantity++;
        }
        else
        {
            Node<T>* current = head;
            while (current ->next != nullptr)// бегаем по списку пока не наткнемся на конец
            {
                current = current->next;

            }
            current->next = new Node<T>(item);
            quantity++;
        }
    }
    void InsertToStart(T item)
    {
        if (head == nullptr)
        {
            head = new Node<T>(item);
            quantity++;
        }
        else
        {
            Node<T>* newNode = new Node<T>(item); 
            newNode->next = head; 
            head = newNode; 
            quantity++;
        }

    }
    void SearchByValue(T item)
    {
        Node<T>* current = head;
        while (current != nullptr) 
        {
            if (current->value == item) 
            {
                cout << "Found value: " << current->value << endl;;
                return; 
            }
            current = current->next; 
            index++;
        }
        throw runtime_error("Error: Item not found"); 
    }

    void PrintList()
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->next;
            
        }

    }

};


int main()
{
    LinkedList<int> intList;
    
    return 0;
}