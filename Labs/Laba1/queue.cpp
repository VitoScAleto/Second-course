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

struct Queue
{
private:

    Node<T>* head{ nullptr };

    int sizeList = 0;
    int index = 0;

    bool isValidValue(T item)
    {

        Node<T>* currentPtr = head;

        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {
                return true;
            }
            currentPtr = currentPtr->next;
        }
        return false;
    }


public:

    bool isIntegerInput(int number)
    {
        if (std::cin.fail())
        {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    int getSize()
    {
        return sizeList;
    }

    int GetIndex()
    {
        return index;
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
    
    void pop_back()
    {
        Node<T>* currentPtr = head;
        Node<T>* prevPtr = nullptr;
        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty queue" << endl;
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
  
   
    void printQueue()
    {
        Node<T>* current = head;

        if (current == nullptr)
        {
            cout << "Empty queue" << endl;

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
    Queue <int> intQueue;

    char c;
    cout << "--------------------------------- Queue ---------------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print queue, 2 - push, 3 - pop, 4 - get size\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            intQueue.printQueue();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            int valueInList;
            do
            {
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            } while (intQueue.isIntegerInput(valueInList) == false);
            intQueue.push_front(valueInList);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            intQueue.pop_back();
            cout << endl;
            break;
        }
        case '4':
            cout << endl;
            cout << "Size queue: " << intQueue.getSize() << endl;
            cout << endl;
            break;
        case '0':
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

    return 0;
}