#include "../Headers/stack.h"

template <typename T>

void Stack<T>::writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }

        NodeStack* currentPtr = head;

        while (currentPtr != nullptr)
        {
            outputFile << currentPtr->value << " ";
            currentPtr = currentPtr->next;

        }

        outputFile.close();
    }

template <typename T>

void Stack<T>::readingConfiguration(string nameFile)
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

template <typename T>

void Stack<T>::printStack()
    {
        NodeStack* current = head;

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



template <typename T>

void Stack<T>::pop_front()
    {
        NodeStack* currentPtr = head;

        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty stack" << endl;
            return;
        }
        NodeStack* nextHead = currentPtr->next;

        head = nextHead;
        delete currentPtr;
        sizeList--;
    }

    template <typename T>

void Stack<T>::push_front(T item)
    {
        if (head == nullptr)
        {
            head = new NodeStack(item);
            sizeList++;
        }
        else
        {
            NodeStack* newNodeStack = new NodeStack(item);
            newNodeStack->next = head;
            head = newNodeStack;
            sizeList++;
        }

    }
template <typename T>

int Stack<T>::getSize()
    {
        return sizeList;
    }

template <typename T>

bool Stack<T>::isValidValue(T item)
    {

        NodeStack* currentPtr = head;

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


int FunStack()
{
    Stack <string> Stack;

    Stack.readingConfiguration("test.txt");

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
            Stack.printStack();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            string valueInStack;
            
                cout << "Enter value\n\n<<< ";
                cin >> valueInStack;

            
            Stack.push_front(valueInStack);
            cout << endl;
            break;
        }

        case '3':
            cout << endl;
            Stack.pop_front();
            cout << endl;
            break;

        case '4':
            cout << endl;
            cout << "Size stack: " << Stack.getSize() << endl;
            cout << endl;
            break;
        case '0':
            Stack.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }
}