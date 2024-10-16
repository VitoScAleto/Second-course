#include "../Headers/queue.h"




template <typename T>

void Queue<T>::writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }

        NodeQueue* currentPtr = head;

        while (currentPtr != nullptr)
        {
            outputFile << currentPtr->value << " ";
            currentPtr = currentPtr->next;

        }

        outputFile.close();
    }

template <typename T>

void Queue<T>::readingConfiguration(string nameFile)
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

void Queue<T>::printQueue()
    {
        NodeQueue* current = head;

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

template <typename T>

void Queue<T>::pop_back()
    {
        NodeQueue* currentPtr = head;
        NodeQueue* prevPtr = nullptr;
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


template <typename T>

void Queue<T>::push_front(T item)
    {
        if (head == nullptr)
        {
            head = new NodeQueue(item);
            sizeList++;
        }
        else
        {
            NodeQueue* newNodeQueue = new NodeQueue(item);
            newNodeQueue->next = head;
            head = newNodeQueue;
            sizeList++;
        }
        
    }

template <typename T>

int Queue<T>:: getSize()
    {
        return sizeList;
    }


template <typename T>

bool Queue<T>::isValidValue(T item)
    {

        NodeQueue* currentPtr = head;

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
