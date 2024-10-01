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

struct Queue
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

    void readingConfiguration(string nameFile)
    {
        string valueConfiguration;

        ifstream inputFile(nameFile);

        if (!inputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }
        while (inputFile >> valueConfiguration)
        {
            push_front(valueConfiguration);
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
    Queue <string> Queue;

    Queue.readingConfiguration("test.txt");

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
            Queue.printQueue();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            string valueInList;
          
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            
            Queue.push_front(valueInList);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            Queue.pop_back();
            cout << endl;
            break;
        }
        case '4':
            cout << endl;
            cout << "Size queue: " << Queue.getSize() << endl;
            cout << endl;
            break;
        case '0':
            Queue.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

}