#include <iostream>
#include <fstream>

using namespace std;

template <typename T>

struct Node
{
    T value;
    Node* next;
    Node* prevToNode;
    Node(T val) : value(val), next(nullptr), prevToNode(nullptr) {}; // Constructor for initializing value
};

template <typename T>

struct DLinkedList
{
private:

    Node<T>* head{ nullptr };
    Node<T>* tail{ nullptr };

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
        if (cin.fail())
        {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    void getSize()
    {
        cout << "Size list: " << sizeList << endl;
    }

    void push_back(T item)
    {
        Node<T>* currentPtr = new Node<T>(item);
        if (head == nullptr)
        {
            head = currentPtr;
            tail = currentPtr;
        }
        else
        {
            tail->next = currentPtr;
            currentPtr->prevToNode = tail;
            tail = currentPtr;
        }
        sizeList++;
    }

    void push_front(T item)
    {
        Node<T>* currentPtr = new Node<T>(item);

        if (head == nullptr)
        {
            head = currentPtr;
            tail = currentPtr;
        }
        else
        {
            currentPtr->next = head;
            head->prevToNode = currentPtr;
            head = currentPtr;
        }
        sizeList++;
    }

    void pop_back()
    {
        if (tail == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }

        if (tail == head)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T>* currentPtr = tail;
            tail = tail->prevToNode;
            tail->next = nullptr;
            delete currentPtr;
        }
        sizeList--;
    }

    void pop_front()
    {

        if (tail == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }

        if (tail == head)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T>* currentPtr = head;
            head = head->next;
            head->prevToNode = nullptr;
            delete currentPtr;
        }
        sizeList--;


    }


    void delete_by_value(T item)
    {
        if (isValidValue(item) == false)
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        Node<T>* currentPtr = head;


        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {

                if (currentPtr->prevToNode)
                {
                    currentPtr->prevToNode->next = currentPtr->next;
                }
                else
                {
                    head = currentPtr->next;
                }
                if (currentPtr->next)
                {
                    currentPtr->next->prevToNode = currentPtr->prevToNode;
                }
                Node<T>* toDelete = currentPtr;
                currentPtr = currentPtr->next;
                delete toDelete;
                sizeList--;
            }
            else
            {
                currentPtr = currentPtr->next;
            }
        }


    }

    void printList()
    {
        if (head == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }

        Node<T>* currentPtr = head;

        while (currentPtr != nullptr)
        {
            cout << currentPtr->value << " ";
            currentPtr = currentPtr->next;
        }
        cout << endl;
    }

    void search_by_value(T item)
    {
        if (isValidValue(item) == false)
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        Node<T>* currentPtr = head;

        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {
                cout << "Value: " << currentPtr->value << " index: " << index;
                cout << endl;
            }

            currentPtr = currentPtr->next;
            index++;
        }
    }

    void readingConfiguration(string nameFile)
    {
        int valueConfiguration = 0;

        ifstream inputFile(nameFile);

        if (!inputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }
        while (inputFile >> valueConfiguration)
        { 
            push_back(valueConfiguration);
        }

        inputFile.close();
    }

    void writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }

        Node<T>* currentPtr = head;

        while (currentPtr != nullptr)
        {
            outputFile << currentPtr->value << " ";
            currentPtr = currentPtr->next;

        }

        outputFile.close();
    }
};

int main()
{
    DLinkedList <int> DList;

    DList.readingConfiguration("test.txt");

    char c;

    cout << "\t\t--------------------------Doubly Linked List--------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print list, 2 - push_front, 3 - push_back, 4 - pop_back, 5 - pop_front, 6 - search by value, 7 - delete by value, 8 - get size\n\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            DList.printList();
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

            } while (DList.isIntegerInput(valueInList) == false);
            DList.push_front(valueInList);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            int valueInList;
            do
            {
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            } while (DList.isIntegerInput(valueInList) == false);
            DList.push_back(valueInList);
            cout << endl;
            break;
        }
        case '4':
            cout << endl;
            DList.pop_back();
            cout << endl;
            break;
        case '5':
            cout << endl;
            DList.pop_front();
            cout << endl;
            break;
        case '6':
        {
            cout << endl;
            int valueInList;
            do
            {
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            } while (DList.isIntegerInput(valueInList) == false);
            DList.search_by_value(valueInList);
            cout << endl;
            break;
        }
        case '7':
        {
            cout << endl;
            int valueInList;
            do
            {
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            } while (DList.isIntegerInput(valueInList) == false);
            DList.delete_by_value(valueInList);
            cout << endl;
            break;
        }
        case '8':
            cout << endl;
            DList.getSize();
            cout << endl;
            break;
        case '0':
            DList.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

   

    return 0;
}
