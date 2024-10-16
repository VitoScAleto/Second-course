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
        if (!inputFile)
        {
            ofstream outputFile(nameFile);
            if(!outputFile)
            {
                cerr<<"Не удалось создать файл "<< nameFile<<endl;
                return;
            }
            outputFile.close();
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
