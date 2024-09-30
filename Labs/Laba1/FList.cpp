#include <iostream>
#include <fstream>

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

        if (isValidValue(item) == false)
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

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

        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }
        Node<T>* nextHead = currentPtr->next;

        head = nextHead;
        delete currentPtr;
        sizeList--;
    }

    void delete_by_value(T item)
    {
        if (!isValidValue(item))
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        Node<T>* currentPtr = head;
        Node<T>* prevPtr = nullptr;

        if (currentPtr == nullptr)
        {
            cerr << "Empty list" << endl;
            return;
        }

        while (currentPtr != nullptr && currentPtr->value == item)
        {
            Node<T>* temp = currentPtr;
            currentPtr = currentPtr->next;
            delete temp;
            head = currentPtr;
            sizeList--;
        }


        prevPtr = head;
        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {
                prevPtr->next = currentPtr->next;
                delete currentPtr;
                currentPtr = prevPtr->next;
                sizeList--;
            }
            else
            {
                prevPtr = currentPtr;
                currentPtr = currentPtr->next;
            }
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
    LinkedList <int> intList;

    intList.readingConfiguration("test.txt");

    char c;
    cout << "--------------------------------- Linked List ---------------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print list, 2 - push_front, 3 - push_back, 4 - pop_back, 5 - pop_front, 6 - search by value, 7 - delete by value, 8 - get size\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            intList.printList();
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
        {
            cout << endl;
            int valueInList;
            do
            {
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            } while (intList.isIntegerInput(valueInList) == false);
            intList.push_back(valueInList);
            cout << endl;
            break;
        }
        case '4':
            cout << endl;
            intList.pop_back();
            cout << endl;
            break;
        case '5':
            cout << endl;
            intList.pop_front();
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

            } while (intList.isIntegerInput(valueInList) == false);
            intList.search_by_value(valueInList);
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

            } while (intList.isIntegerInput(valueInList) == false);
            intList.delete_by_value(valueInList);
            cout << endl;
            break;
        }
        case '8':
            cout << endl;
            cout << "Size list: " << intList.getSize() << endl;
            cout << endl;
            break;
        case '0':
            intList.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

    return 0;
}