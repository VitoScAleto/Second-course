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
    int sizeList = 0;
    int index = 0;

public:
    int getSize()
    {
        return sizeList;
    }
    int GetIndex()
    {
        return index;
    }
    void push_back(T item)
    {
        if (head == nullptr)
        {
            head = new Node<T>(item);
            sizeList++;
        }
        else
        {
            Node<T>* current = head;
            while (current->next != nullptr)
            {
                current = current->next;

            }
            current->next = new Node<T>(item);
            sizeList++;
        }
    }
    void push_front(T item)
    {
        if (head == nullptr)
        {
            head = new Node<T>(item);
            sizeList++;
        }
        else
        {
            Node<T>* newNode = new Node<T>(item);
            newNode->next = head;
            head = newNode;
            sizeList++;
        }

    }
    void search_by_value(T item)
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            if (current->value == item)
            {
                cout << "Found value: " << current->value << "Index: " << index << endl;
            }
            current = current->next;
            index++;
        }

    }
    void pop_back()
    {
        Node<T>* currentPtr = head;
        Node<T>* prevPtr = nullptr;
        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }
        else if (currentPtr->next == nullptr)
        {
            delete currentPtr;
            head = nullptr;
            sizeList--;
            return;
        }
        while (currentPtr->next != nullptr)
        {
            prevPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        free(currentPtr);
        prevPtr->next = nullptr;
        sizeList--;
    }
    void pop_front()
    {
        Node<T>* currentPtr = head;
        Node<T>* nextHead = currentPtr->next;
        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }
        head = nextHead;
        delete currentPtr;
        sizeList--;
    }

    void delete_by_value(T item)
    {
        Node<T>* currentPtr = head;
        Node<T>* prevPtr = nullptr;

        if (currentPtr == nullptr)
        {
            cerr << "Empty list" << endl;// список пуст
            return;
        }
        else if (currentPtr->next == nullptr)// один элемент
        {
            delete head;
            delete currentPtr;
            sizeList--;
            return;
        }
        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item && currentPtr == head)// если значение голова списка
            {
                pop_front();
                sizeList--;
                return;
            }
            else if (currentPtr->value == item)
            {
                prevPtr->next = currentPtr->next;
                delete currentPtr;
                sizeList--;
                return;

            }
            prevPtr = currentPtr;
            currentPtr = currentPtr->next;
        }

    }
    void printList()
    {
        Node<T>* current = head;
        if (current == nullptr)
        {
            cout << "Empty list" << endl;

        }
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->next;

        }
        cout << endl;
    }

};


int main()
{
    LinkedList <int> intList;

    char c;

    while (true)
    {
        cout << "0 - exit, 1 - print list, 2 - push_front, 3 - push_back, 4 - pop_back, 5 - pop_front, 6 - search by value, 7 - delete by value, 8 - get size\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            intList.printList();
            cout << endl;
            break;
        case '2':
        {
            int valueInList;
            cout << "Enter value\n<<< ";
            cin >> valueInList;
            intList.push_front(valueInList);
            cout << endl;
            break;
        }
        case '3':
        {
            int valueInList;
            cout << "Enter value\n<<< ";
            cin >> valueInList;
            intList.push_back(valueInList);
            cout << endl;
            break;
        }
        case '4':
            intList.pop_back();
            cout << endl;
            break;
        case '5':
            intList.pop_front();
            cout << endl;
            break;
        case '6':
        {
            int valueInList;
            cout << "Enter value to search\n<<< ";
            cin >> valueInList;
            intList.search_by_value(valueInList);
            cout << endl;
            break;
        }
        case '7':
        {
            int valueInList;
            cout << "Enter value to delete\n<<< ";
            cin >> valueInList;
            intList.delete_by_value(valueInList);
            cout << endl;
            break;
        }
        case '8':
            intList.getSize();
            cout << endl;
            break;
        case '0':
            return 0;
        default:
            cout << "Unknown command. Re-enter" << endl;
            break;
        }
    }

    return 0;
}