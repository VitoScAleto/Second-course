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


    void pop_front()
    {
        Node<T>* currentPtr = head;

        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty stack" << endl;
            return;
        }
        Node<T>* nextHead = currentPtr->next;

        head = nextHead;
        delete currentPtr;
        sizeList--;
    }


    void printStack()
    {
        Node<T>* current = head;

        if (current == nullptr)
        {
            cout << "Empty stack" << endl;

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
    cout << "--------------------------------- Stack ---------------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print stack, 2 - push, 3 - pop_front, 4 - get size\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            intList.printStack();
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

            } while (intList.isIntegerInput(valueInList) == false);
            intList.push_front(valueInList);
            cout << endl;
            break;
        }

        case '3':
            cout << endl;
            intList.pop_front();
            cout << endl;
            break;

        case '4':
            cout << endl;
            cout << "Size stack: " << intList.getSize() << endl;
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